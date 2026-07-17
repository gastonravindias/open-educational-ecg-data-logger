/*
  Solar-Assisted Educational ECG Data Logger
  Reference firmware release v1.0.0

  SPDX-License-Identifier: MIT

  Intended use:
  - supervised biomedical-engineering education
  - non-clinical bench demonstrations
  - raw ADC and status logging

  Not a medical device. No diagnostic or heart-rate interpretation is implemented.
  Quantitative testing should use an ECG simulator or calibrated signal source.
*/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>
#include <RTClib.h>
#include <cmath>

namespace Pins {
constexpr uint8_t ECG_OUT = 0;
constexpr uint8_t ECG_LO_PLUS = 1;
constexpr uint8_t BUZZER = 2;       // active-low
constexpr uint8_t ECG_LO_MINUS = 3;
constexpr uint8_t SD_SCK = 4;
constexpr uint8_t SD_MISO = 5;
constexpr uint8_t SD_MOSI = 6;
constexpr uint8_t SD_CS = 7;
constexpr uint8_t ECG_SDN = 10;
constexpr uint8_t I2C_SDA = 20;
constexpr uint8_t I2C_SCL = 21;
}

constexpr uint32_t SERIAL_BAUD = 115200;
constexpr uint32_t SAMPLE_PERIOD_US = 4000;     // nominal 250 samples/s
constexpr uint32_t DISPLAY_PERIOD_MS = 50;      // 20 display updates/s
constexpr uint32_t POWER_PERIOD_MS = 1000;
constexpr uint32_t FLUSH_PERIOD_MS = 1000;
constexpr uint8_t OLED_ADDRESS = 0x3C;
constexpr int OLED_WIDTH = 128;
constexpr int OLED_HEIGHT = 64;

// Disabled by default because the INA219 connection point and battery chemistry
// must be verified before voltage thresholds are used.
constexpr bool ENABLE_POWER_THRESHOLDS = false;
constexpr float LOW_POWER_V = 3.45F;
constexpr float CRITICAL_POWER_V = 3.25F;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
Adafruit_INA219 ina219;
RTC_DS3231 rtc;
File logFile;

enum class SystemState : uint8_t {
  Normal = 0,
  LeadOff = 1,
  SdFault = 2,
  LowPower = 3,
  CriticalPower = 4
};

bool oledReady = false;
bool rtcReady = false;
bool inaReady = false;
bool sdReady = false;

uint32_t nextSampleUs = 0;
uint32_t lastDisplayMs = 0;
uint32_t lastPowerMs = 0;
uint32_t lastFlushMs = 0;
uint32_t missedIntervals = 0;
uint32_t sampleCount = 0;

float busVoltageV = NAN;
float currentmA = NAN;
float powermW = NAN;
int lastPlotY = 50;
uint8_t plotX = 0;

const char* stateName(SystemState state) {
  switch (state) {
    case SystemState::Normal: return "NORMAL";
    case SystemState::LeadOff: return "LEAD_OFF";
    case SystemState::SdFault: return "SD_FAULT";
    case SystemState::LowPower: return "LOW_POWER";
    case SystemState::CriticalPower: return "CRITICAL_POWER";
  }
  return "UNKNOWN";
}

SystemState determineState(bool leadOff) {
  if (!sdReady) return SystemState::SdFault;
  if (leadOff) return SystemState::LeadOff;
  if (ENABLE_POWER_THRESHOLDS && !std::isnan(busVoltageV)) {
    if (busVoltageV <= CRITICAL_POWER_V) return SystemState::CriticalPower;
    if (busVoltageV <= LOW_POWER_V) return SystemState::LowPower;
  }
  return SystemState::Normal;
}

void setWarningOutput(SystemState state, uint32_t nowMs) {
  bool warning = state != SystemState::Normal;
  bool pulseOn = warning && ((nowMs / 250U) % 4U == 0U);
  digitalWrite(Pins::BUZZER, pulseOn ? LOW : HIGH);
}

void updatePowerTelemetry(uint32_t nowMs) {
  if (!inaReady || nowMs - lastPowerMs < POWER_PERIOD_MS) return;
  lastPowerMs = nowMs;
  busVoltageV = ina219.getBusVoltage_V();
  currentmA = ina219.getCurrent_mA();
  powermW = ina219.getPower_mW();
}

void drawDisplay(int adcRaw, bool leadOff, SystemState state, uint32_t nowMs) {
  if (!oledReady || nowMs - lastDisplayMs < DISPLAY_PERIOD_MS) return;
  lastDisplayMs = nowMs;

  if (plotX == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
  }

  display.fillRect(0, 0, OLED_WIDTH, 16, SSD1306_BLACK);
  display.setCursor(0, 0);
  display.print(stateName(state));
  display.setCursor(0, 8);
  display.print("ADC:");
  display.print(adcRaw);
  if (leadOff) display.print(" LEAD");

  int y = map(constrain(adcRaw, 0, 4095), 0, 4095, 62, 18);
  display.drawLine(plotX == 0 ? 0 : plotX - 1, lastPlotY, plotX, y, SSD1306_WHITE);
  lastPlotY = y;
  plotX++;
  if (plotX >= OLED_WIDTH) plotX = 0;
  display.display();
}

void createLogFile() {
  if (!sdReady) return;

  char filename[40] = "/ECG_BOOT.csv";
  if (rtcReady) {
    DateTime now = rtc.now();
    snprintf(filename, sizeof(filename), "/ECG_%04d%02d%02d_%02d%02d%02d.csv",
             now.year(), now.month(), now.day(),
             now.hour(), now.minute(), now.second());
  }

  logFile = SD.open(filename, FILE_WRITE);
  if (!logFile) {
    sdReady = false;
    return;
  }

  logFile.println(
    "sample,elapsed_us,rtc_unix,adc_raw,lead_off,state,"
    "bus_voltage_V,current_mA,power_mW,missed_intervals");
  logFile.flush();
}

void setup() {
  pinMode(Pins::ECG_LO_PLUS, INPUT);
  pinMode(Pins::ECG_LO_MINUS, INPUT);
  pinMode(Pins::ECG_SDN, OUTPUT);
  pinMode(Pins::BUZZER, OUTPUT);
  pinMode(Pins::SD_CS, OUTPUT);

  digitalWrite(Pins::ECG_SDN, HIGH);
  digitalWrite(Pins::BUZZER, HIGH);
  digitalWrite(Pins::SD_CS, HIGH);

  Serial.begin(SERIAL_BAUD);
  delay(200);

  analogReadResolution(12);
  Wire.begin(Pins::I2C_SDA, Pins::I2C_SCL);

  oledReady = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  if (oledReady) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ECG logger v1.0");
    display.println("Educational only");
    display.display();
  }

  rtcReady = rtc.begin();
  inaReady = ina219.begin();

  SPI.begin(Pins::SD_SCK, Pins::SD_MISO, Pins::SD_MOSI, Pins::SD_CS);
  sdReady = SD.begin(Pins::SD_CS, SPI, 8000000U);
  createLogFile();

  nextSampleUs = micros();
  lastDisplayMs = millis();
  lastPowerMs = millis();
  lastFlushMs = millis();
}

void loop() {
  uint32_t nowUs = micros();
  int32_t untilSample = static_cast<int32_t>(nowUs - nextSampleUs);
  if (untilSample < 0) return;

  if (untilSample >= static_cast<int32_t>(SAMPLE_PERIOD_US)) {
    uint32_t skipped = static_cast<uint32_t>(untilSample) / SAMPLE_PERIOD_US;
    missedIntervals += skipped;
    nextSampleUs += skipped * SAMPLE_PERIOD_US;
  }
  nextSampleUs += SAMPLE_PERIOD_US;

  uint32_t nowMs = millis();
  updatePowerTelemetry(nowMs);

  bool leadOff = digitalRead(Pins::ECG_LO_PLUS) == HIGH ||
                 digitalRead(Pins::ECG_LO_MINUS) == HIGH;
  int adcRaw = analogRead(Pins::ECG_OUT);
  SystemState state = determineState(leadOff);
  setWarningOutput(state, nowMs);

  uint32_t rtcUnix = rtcReady ? rtc.now().unixtime() : 0U;
  uint32_t elapsedUs = micros();

  Serial.print(elapsedUs);
  Serial.print(',');
  Serial.print(adcRaw);
  Serial.print(',');
  Serial.print(leadOff ? 1 : 0);
  Serial.print(',');
  Serial.println(stateName(state));

  if (sdReady && logFile) {
    char line[180];
    snprintf(line, sizeof(line),
             "%lu,%lu,%lu,%d,%u,%s,%.3f,%.3f,%.3f,%lu\n",
             static_cast<unsigned long>(sampleCount),
             static_cast<unsigned long>(elapsedUs),
             static_cast<unsigned long>(rtcUnix),
             adcRaw,
             leadOff ? 1U : 0U,
             stateName(state),
             static_cast<double>(busVoltageV),
             static_cast<double>(currentmA),
             static_cast<double>(powermW),
             static_cast<unsigned long>(missedIntervals));
    logFile.print(line);

    if (nowMs - lastFlushMs >= FLUSH_PERIOD_MS) {
      logFile.flush();
      lastFlushMs = nowMs;
    }
  }

  drawDisplay(adcRaw, leadOff, state, nowMs);
  sampleCount++;
}

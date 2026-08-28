# Assembly Guide v1.1 — Educational ECG Data Logger

## Scope and safety gate

This guide is for supervised educational bench work. The open breadboard **must not be attached to a person**. Use an ECG simulator for waveform-acquisition exercises and an appropriate calibrated low-voltage source for ADC-characterisation exercises.

The design has no documented certified patient-isolation barrier or leakage-current validation. Before any build activity, review `safety/safety_policy.md` and `safety/risk_assessment.csv`.

## Required preparation

Before assembly:

1. Confirm the ESP32-C3 board is a 3.3 V-logic device and identify the GPIO labels physically present on the board.
2. Confirm the AD8232 breakout exposes `OUT`, `LO+`, `LO-`, `SDN`, `3.3 V` and `GND`.
3. Confirm the OLED, RTC, INA219 and microSD modules are electrically compatible with 3.3 V ESP32-C3 operation.
4. Use a protected 1S Li-ion/LiPo battery-derived supply through a regulator that can be set and verified at 3.3 V.
5. Keep the AD8232 simulator lead cable disconnected while programming or using USB.
6. Keep a digital multimeter available for rail-voltage and polarity checks.

## Reference pin map

| Function | ESP32-C3 pin |
|---|---|
| I²C SDA | GPIO20 |
| I²C SCL | GPIO21 |
| microSD SCK | GPIO4 |
| microSD MISO | GPIO5 |
| microSD MOSI | GPIO6 |
| microSD CS | GPIO7 |
| AD8232 OUT | GPIO0 |
| AD8232 LO+ | GPIO1 |
| AD8232 LO- | GPIO3 |
| AD8232 SDN | GPIO10 |
| Active-low buzzer IN | GPIO2 |

The same mapping is provided in `hardware/pin_map.csv`.

## Stage 1 — establish the regulated power rail

1. Connect only the protected battery and regulator.
2. Set the regulator output to 3.3 V.
3. Measure the output with a DMM before connecting any module.
4. Confirm correct polarity and common-ground continuity.

**Expected result:** a stable 3.3 V rail.

**If the stage fails:** stop. Do not connect modules until the rail is stable and polarity is correct.

## Stage 2 — ESP32-C3 and OLED bring-up

1. Connect the ESP32-C3 to the verified 3.3 V rail and GND.
2. Connect the SSD1306 OLED to 3.3 V/GND.
3. Connect SDA to GPIO20 and SCL to GPIO21.
4. Keep the AD8232 simulator lead cable physically disconnected.
5. Program the reference firmware.
6. Restart the controller from the battery-derived rail.

**Expected result:** the OLED initialises and displays a startup/status screen even without an ECG input.

**Diagnostics if not obtained:**
- confirm SDA/SCL are not reversed;
- confirm common ground;
- confirm OLED supply compatibility;
- run an I²C scan and verify the actual device address;
- inspect breadboard contact continuity.

## Stage 3 — add the DS3231 RTC

1. Connect the RTC to the existing I²C bus.
2. Confirm 3.3 V-compatible interface operation.
3. Restart the system.

**Expected result:** an RTC/time field appears and advances.

**Diagnostics if not obtained:** check the RTC address, supply, common ground and I²C pull-ups; verify that the new device has not caused a bus conflict.

## Stage 4 — add microSD storage

1. Use a microSD interface compatible with 3.3 V logic.
2. Connect SCK to GPIO4, MISO to GPIO5, MOSI to GPIO6 and CS to GPIO7.
3. Insert a suitable formatted card.
4. Start the firmware.

**Expected result:** storage initialises and the firmware can create a CSV file/header.

**Diagnostics if not obtained:** check card format, CS assignment, supply voltage, logic-level compatibility, ground and SPI wiring.

## Stage 5 — add the AD8232 without a simulator

1. Connect AD8232 `3.3 V` and `GND`.
2. Connect `OUT` to GPIO0.
3. Connect `LO+` to GPIO1.
4. Connect `LO-` to GPIO3.
5. Connect `SDN` to GPIO10.
6. Leave the RA/LA/RL-style simulator cable disconnected.

**Expected result:** raw ADC counts are available and the firmware reports a disconnected-lead/open-input state where implemented.

**Interpretation:** a floating or noisy input at this stage is **not an ECG** and must not be described as one.

## Stage 6 — optional INA219 and buzzer

### INA219
Connect the INA219 to 3.3 V/GND and the shared I²C bus on GPIO20/GPIO21.

**Expected result:** the device is detected and available telemetry fields are populated.

### Buzzer
Connect a 3.3 V-compatible active-low buzzer input to GPIO2.

**Expected result:** the configured status/alarm logic can drive the buzzer.

These modules are optional for the core ECG-acquisition lesson.

## Stage 7 — connect an ECG simulator

1. Ensure USB, charging and externally powered test equipment are disconnected from the AD8232 lead interface.
2. Configure a suitable ECG simulator according to its manufacturer instructions.
3. Connect the simulator to the RA/LA/RL-style lead terminals.
4. Start logging.
5. Record the simulator make/model and settings with the run.

**Expected result:** a periodic simulator-derived waveform is observed and CSV logging proceeds.

**If clipped, flat or unstable:** check simulator level, lead mapping, saturation, common ground, lead-off status and loose breadboard connections.

## Stage 8 — preserve and inspect the data

For every quantitative replication:

1. Preserve the raw CSV file.
2. Record firmware commit/tag.
3. Record ESP32 core/board and external-library versions.
4. Record simulator settings or calibration-source values.
5. Plot raw ADC counts versus sample index and/or logged elapsed time.
6. Do not convert ADC counts to volts unless a separate calibration experiment has established the board-specific relationship.

## Troubleshooting strategy

Return to the last stage that passed and add only one subsystem at a time. Common faults include:

- swapped SDA/SCL;
- incorrect microSD CS pin;
- incompatible microSD logic voltage;
- missing common ground;
- loose breadboard contacts;
- open simulator lead;
- ADC saturation;
- unstable regulator output; and
- unintended USB/external-power connection.

## Evidence rule

Do not reconstruct missing historical measurements. New quantitative claims must point to newly generated, preserved raw data.

# Assembly guide

## Validated scope
The retained evidence supports the original breadboard integration, OLED output and qualitative serial streaming. The guide is for supervised educational reconstruction and not for clinical use.

## Core build sequence
1. Inspect the ESP32-C3 pin labels against `hardware/pin_map.csv`.
2. Connect the SSD1306, DS3231 and INA219 to the shared I²C bus: SDA GPIO20 and SCL GPIO21.
3. Connect the microSD module: SCK GPIO4, MISO GPIO5, MOSI GPIO6 and CS GPIO7.
4. Connect the AD8232: OUT GPIO0, LO+ GPIO1, LO- GPIO3 and SDN GPIO10.
5. Connect the active-low buzzer input to GPIO2.
6. Confirm common ground and appropriate module supply voltages.
7. Load the reference firmware.
8. Verify OLED startup without electrodes.
9. Verify SD file creation using a bench signal source or open-input test.
10. Perform quantitative testing only with an ECG simulator or calibrated source.

## Safety
- Do not connect a person to the open breadboard.
- Electrode-connected demonstrations must be battery-only.
- Disconnect USB, charging and externally powered instruments before electrode connection.
- Disconnect electrodes before programming or serial debugging.
- Do not infer battery series/parallel wiring from photographs.

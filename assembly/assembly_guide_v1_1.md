# Assembly Guide v1.1 — Educational ECG Data Logger

## Safety gate
This open breadboard is not for human attachment. Use an ECG simulator for waveform exercises. The design has no documented medical isolation or leakage-current validation.

Use a protected battery-derived regulated 3.3 V supply. Disconnect the AD8232 lead cable before USB programming, charging, or connection to mains-powered instruments.

## Reference pin map
- I2C SDA: GPIO20
- I2C SCL: GPIO21
- microSD SCK: GPIO4
- microSD MISO: GPIO5
- microSD MOSI: GPIO6
- microSD CS: GPIO7
- AD8232 OUT: GPIO0
- AD8232 LO+: GPIO1
- AD8232 LO-: GPIO3
- AD8232 SDN: GPIO10
- active-low buzzer IN: GPIO2

## Staged build
1. **Power rail:** regulator only; set and verify 3.3 V with a DMM; check polarity/ground.
2. **ESP32-C3 + OLED:** load firmware with AD8232 lead cable disconnected; confirm OLED startup without analogue input.
3. **RTC:** add DS3231 to I2C; confirm time field advances.
4. **microSD:** add 3.3 V-compatible SPI module; confirm card initialises and CSV file/header is created.
5. **AD8232, no simulator:** connect OUT/LO+/LO-/SDN; confirm raw counts and disconnected-lead status. Do not call a floating-input trace ECG.
6. **ECG simulator:** attach RA/LA/RL-style leads to the simulator; confirm periodic waveform and logging.
7. **Preserve data:** save raw CSV, simulator settings, firmware tag/commit, board/core/library versions and analysis code.

Troubleshooting should proceed by returning to the last passed stage. Common faults are swapped SDA/SCL, wrong CS, incompatible microSD logic voltage, loose ground, lead-off, saturation and unstable breadboard contacts.

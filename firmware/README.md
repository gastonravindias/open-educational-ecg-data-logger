# Reference firmware

`solar_ecg_educational_logger_v1_0.ino` is a transparent reference implementation reconstructed from the documented hardware architecture and pin map.

## Code-defined configuration
- ESP32-C3
- 12-bit raw ADC logging
- nominal 250 samples/s (`4000 µs` schedule)
- I²C on GPIO20/GPIO21
- microSD SPI on GPIO4/GPIO5/GPIO6/GPIO7
- AD8232 OUT GPIO0, LO+ GPIO1, LO- GPIO3, SDN GPIO10
- active-low buzzer GPIO2
- no diagnostic interpretation
- no heart-rate or arrhythmia algorithm
- no trained AI model
- battery thresholds disabled until the actual sensing point and battery chemistry are verified

The code-defined sampling interval is not a measured timing-accuracy claim. Hardware users should run the supplied validation protocol.

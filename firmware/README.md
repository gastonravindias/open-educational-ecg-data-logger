# Reference firmware

The current reviewer-revised firmware is:

`ecg_educational_logger_v1_1.ino`

The earlier solar-named firmware remains preserved in the archived v1.0.0 release for provenance; it is not part of the v1.1.0 current tree.

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

The code-defined sampling interval is not a measured timing-accuracy claim. The firmware records raw ADC counts; count-to-voltage conversion was not experimentally validated for the historical prototype.

## Current supporting documentation

- Dependencies/version guidance: `library_versions_v1_1.md`
- Assembly guide: `../assembly/assembly_guide_v1_1.md`
- Educational test protocol: `../testing/educational_lab_protocol_v1_1.md`
- Safety policy: `../safety/safety_policy.md`

## Safety

Do not attach the open breadboard to a person. Programming, USB, charging and externally powered bench equipment are used only with the AD8232 lead cable disconnected.

# Open Educational ECG Acquisition and Data-Logging Platform

**Reviewer-revision version: v1.1.0**

Repository: https://github.com/gastonravindias/open-educational-ecg-data-logger

Archived original release v1.0.0: https://doi.org/10.5281/zenodo.21404685

> A preserved Zenodo release corresponding to v1.1.0 will be created after completion of repository synchronisation.

## Purpose

This project documents an open educational ECG acquisition and data-logging platform based on the AD8232 analogue front end and ESP32-C3 microcontroller.

The platform is intended for supervised biomedical-engineering, electrical-engineering, embedded-systems, and open-hardware education. It allows learners to study the complete signal pathway from analogue-front-end acquisition through raw ADC sampling, local display, time stamping, storage, subsystem diagnostics, and data analysis.

The platform is an educational prototype and is not a medical device.

## Revised educational core

The v1.1.0 instructional configuration consists of:

- ECG simulator or appropriate calibrated low-voltage source;
- AD8232 analogue front end;
- ESP32-C3 controller;
- SSD1306 OLED display;
- DS3231 real-time clock;
- microSD CSV logging;
- optional INA219 power telemetry; and
- protected battery-derived regulated 3.3 V supply.

The solar subsystem included in the historical prototype is **not part of the v1.1.0 educational core**. Solar-specific design material remains preserved in the archived v1.0.0 release for provenance but is omitted from the current reviewer-revised tree.

## Educational objectives

The platform can be used to teach:

- breadboard-based biomedical instrumentation assembly;
- analogue-front-end and embedded-system signal pathways;
- I²C and SPI peripheral integration;
- staged hardware bring-up and fault isolation;
- raw ADC acquisition;
- microSD-based CSV logging;
- lead-off status monitoring;
- ECG-simulator waveform acquisition;
- plotting and inspection of recorded data;
- ADC characterisation;
- reproducible experimental documentation; and
- open-hardware versioning, licensing, and FAIR practice.

## Evidence boundary

One original breadboard prototype was assembled and demonstrated.

Retained evidence includes:

- prototype and subsystem photographs;
- OLED output photographs;
- qualitative serial-plotter waveform photographs; and
- reference firmware and hardware documentation.

The original project archive does **not** contain:

- the numerical raw ECG/ADC dataset corresponding to the retained serial-plotter photographs;
- a traceable amplitude-calibration dataset;
- measured ADC gain, offset, or linearity data;
- measured sampling jitter or dropped-sample results;
- long-duration microSD reliability measurements;
- independent replication data; or
- validated clinical or diagnostic performance data.

These missing historical measurements have not been reconstructed or invented.

The firmware records raw ADC counts. Count-to-voltage conversion has not been experimentally validated for the historical prototype. The nominal 12-bit ADC configuration and 4000 microsecond scheduling interval (nominal 250 samples/s) are code-defined settings, not experimentally validated performance specifications.

## Safety

**Do not attach the open breadboard to a person.**

Human physiological acquisition is outside the permitted use of this educational build.

Waveform exercises should use a battery-operated or appropriately isolated ECG simulator according to its manufacturer instructions. ADC-characterisation exercises may use an appropriate calibrated low-voltage source.

The prototype has no documented:

- certified patient-isolation barrier;
- leakage-current validation;
- medical electrical-safety validation;
- protective clinical enclosure; or
- validated patient-input protection network.

USB programming, charging, mains-powered computers, oscilloscopes, and other externally powered equipment must be disconnected from the AD8232 lead interface before the simulator lead cable is attached.

The AD8232 lead cable must be disconnected before programming, charging, serial debugging, or connection to externally powered test equipment.

See `safety/safety_policy.md` and `safety/risk_assessment.csv`.

## Repository navigation

| Area | Current v1.1.0 resource |
|---|---|
| Assembly | `assembly/assembly_guide_v1_1.md` |
| Bill of materials | `bom/BOM_v1_1.csv` |
| Editable wiring | `hardware/editable_source/wiring_diagram_v1_1.svg` |
| Wiring export | `hardware/exports/wiring_diagram_v1_1.png` |
| Pin map | `hardware/pin_map.csv` |
| Firmware | `firmware/ecg_educational_logger_v1_1.ino` |
| Software dependencies | `firmware/library_versions_v1_1.md` |
| Educational testing | `testing/educational_lab_protocol_v1_1.md` |
| Evidence matrix | `testing/available_evidence_matrix.csv` |
| FAIR/data statement | `data/DATA_ACCESSIBILITY_FAIR.md` |
| Safety policy | `safety/safety_policy.md` |
| Risk assessment | `safety/risk_assessment.csv` |
| Revised manuscript figures | `figures/` |
| Licences | `licenses/` |

The v1.1.0 firmware uses the solar-free filename `firmware/ecg_educational_logger_v1_1.ino`. The earlier solar-named firmware remains preserved in the archived v1.0.0 release.

## Software dependencies

The reference firmware uses the Arduino ESP32 environment and the following principal libraries or interfaces:

- Wire
- SPI
- SD
- Adafruit_GFX
- Adafruit_SSD1306
- Adafruit_INA219
- RTClib

Exact historical installed library versions were not retained. Future replications should record the operating system, Arduino IDE version, ESP32 board/core version, selected board target, exact external-library versions, firmware commit or release tag, and relevant non-default build settings.

## Reproducibility

Independent replication has not yet been demonstrated.

The repository provides the documentation required for a future independent build: wiring documentation, pin mapping, firmware, BOM, staged assembly guidance, testing procedures, safety controls, dependency documentation, and explicit evidence limitations.

Future replication studies should preserve raw CSV files, ECG-simulator make/model and settings, calibration-source information, firmware version, software dependencies, acquisition conditions, and analysis code.

## FAIR and data accessibility

The project is findable through the public GitHub repository and preserved releases in Zenodo. Common and editable formats are used where practical, including Arduino `.ino`, Markdown, CSV, SVG, and PNG.

The absence of historical numerical waveform and traceable calibration data is explicitly documented rather than retrospectively reconstructed.

See `data/DATA_ACCESSIBILITY_FAIR.md`.

## Clinical and regulatory statement

This project is intended only for education and non-clinical bench prototyping. It is not intended for diagnosis, treatment decisions, clinical monitoring, patient care, unsupervised physiological measurement, or medical-device use.

No IEC 60601-1, IEC 60601-2-47, ISO 14971, diagnostic-performance, or medical-device compliance claim is made.

## Licences

- Hardware design files: CERN Open Hardware Licence Version 2 - Permissive (CERN-OHL-P-2.0)
- Reference firmware: MIT License
- Project documentation and original figures: Creative Commons Attribution 4.0 International (CC BY 4.0)

Third-party hardware, libraries, and vendor resources remain subject to their respective licences and terms.

## Citation and archived releases

The original preserved release is **v1.0.0**:

https://doi.org/10.5281/zenodo.21404685

The reviewer-revised repository state is being prepared as **v1.1.0**. The v1.1.0 Zenodo DOI will be added here after the reviewer-revised release has been archived.

## Scientific integrity statement

No unavailable historical measurement has been recreated or presented as experimental data. Where retained evidence is qualitative, it is identified as qualitative. Where quantitative validation remains necessary, the repository provides a protocol for future reproducible measurement rather than an unsupported retrospective result.

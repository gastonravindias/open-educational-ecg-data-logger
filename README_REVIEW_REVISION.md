# Reviewer revision pack — Open Educational ECG Acquisition and Data-Logging Platform

This pack is designed to be merged into the public repository before resubmission and then preserved as a new versioned release.

## Scientific integrity boundary
The original prototype archive does not contain the numerical serial ECG/ADC data shown in retained plot photographs, a traceable amplitude-calibration dataset, measured timing/dropped-sample data, or independent replication data. These items must not be reconstructed or claimed retrospectively.

## Revised educational core
ECG simulator → AD8232 → ESP32-C3 → OLED / RTC / microSD, with optional INA219 telemetry and a protected battery-derived regulated 3.3 V supply. Human attachment to the open breadboard is prohibited. The solar subsystem is excluded from the revised teaching core.

## Included files
- assembly/assembly_guide_v1_1.md
- bom/BOM_v1_1.csv
- hardware/editable_source/wiring_diagram_v1_1.svg
- hardware/export/wiring_diagram_v1_1.png
- testing/educational_lab_protocol_v1_1.md
- data/DATA_ACCESSIBILITY_FAIR.md
- firmware/library_versions_v1_1.md
- figures/
- REVIEW_REVISION_CHANGELOG.md

Before resubmission, merge these files into the public repository, create a new versioned release, and preserve that exact release in Zenodo so the paper and repository refer to the same state.

# Release v1.1.0 — Peer-review documentation revision

This release was prepared in response to Journal of Open Hardware peer review.

## Main revisions

- Added a substantially expanded undergraduate-oriented assembly guide with staged subsystem bring-up, diagnostics and troubleshooting.
- Added a full component-level connection diagram in editable SVG and exported PNG formats.
- Expanded the bill of materials with quantities, retained identification status, electrical/interface requirements and suitable alternatives.
- Added simulator-centred educational laboratory exercises covering waveform acquisition, plotting, ADC characterisation, timing and storage assessment.
- Added explicit learning objectives, expected observations and common artefacts/failure modes.
- Strengthened the safety policy and risk assessment.
- Human attachment to the open breadboard is prohibited in the revised educational protocol.
- ECG waveform exercises use a battery-operated or appropriately isolated ECG simulator.
- Clarified that the prototype has no documented certified patient-isolation barrier, leakage-current validation or medical electrical-safety validation.
- Added FAIR and data-accessibility documentation.
- Added repository navigation and software dependency/version guidance.
- Clarified that the firmware records raw ADC counts and that historical count-to-voltage conversion was not experimentally validated.
- Explicitly separated code-defined settings from experimentally validated performance.
- Removed the solar subsystem and solar-specific instructional files from the v1.1.0 current tree. The reference firmware was carried forward under the solar-free filename `ecg_educational_logger_v1_1.ino`; the earlier solar-named firmware remains preserved in the archived v1.0.0 release.
- Added revised manuscript figures and reviewer-response documentation.

## Historical evidence boundary

The original prototype archive does not contain:

- the numerical raw ECG/ADC dataset corresponding to the retained serial-plotter photographs;
- a traceable amplitude-calibration dataset;
- measured ADC gain, offset or linearity results;
- measured sampling jitter or dropped-sample results; or
- independent replication data.

These unavailable measurements have not been reconstructed or invented.

The retained visual evidence supports qualitative functional demonstration only. Future quantitative claims should be supported by newly generated and preserved raw data using the revised testing protocol.

---

# Release v1.0.0

- Reframed project as educational open hardware.
- Added transparent reference firmware matching the documented pin map.
- Removed AI-adjacent terminology.
- Added editable wiring source, BOM, assembly guide, evidence matrix, test protocol, safety policy and solar design basis.
- Explicitly documented unavailable measurements and independent replication.

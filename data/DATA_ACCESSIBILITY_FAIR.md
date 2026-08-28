# Data Accessibility and FAIR Statement

## Findable
The project is publicly indexed through GitHub and preserved in Zenodo:

- GitHub: https://github.com/gastonravindias/open-educational-ecg-data-logger
- Zenodo archived release v1.0.0: https://doi.org/10.5281/zenodo.21404685

A new reviewer-revised release will be preserved as v1.1.0 following completion of repository synchronisation.

## Accessible
Project documentation, firmware, hardware design files, testing materials, and supporting resources are publicly accessible through the project repository and preserved release.

## Interoperable
The project uses common and editable file formats, including:

- Arduino `.ino` firmware
- Markdown and plain-text documentation
- CSV tables and data structures
- SVG editable hardware diagrams
- PNG figures and supporting images

These formats are intended to support inspection, modification, reuse, and future replication without dependence on proprietary project-file formats.

## Reusable
Reuse is supported through versioned documentation, build instructions, testing guidance, safety documentation, dependency information, and open licensing.

The project uses:

- CERN Open Hardware Licence Version 2 - Permissive (CERN-OHL-P-2.0) for hardware design files
- MIT License for reference firmware
- Creative Commons Attribution 4.0 International (CC BY 4.0) for project documentation and original figures

## Historical Missing-Data Declaration
The retained original prototype archive does not contain the numerical serial ECG/ADC dataset corresponding to the retained serial-plotter photographs or a traceable amplitude-calibration dataset.

These missing historical data have not been reconstructed, estimated, or presented retrospectively as experimental measurements.

The retained visual evidence therefore supports qualitative functional demonstration only and does not establish calibrated physiological amplitude, diagnostic accuracy, ECG-versus-EMG discrimination, timing accuracy, or other quantitative performance claims.

Future replications should preserve and deposit:

- raw CSV acquisition files;
- ECG simulator make, model, and settings;
- calibration-source information;
- firmware commit or release version;
- exact software and library versions;
- acquisition conditions;
- analysis scripts or notebooks; and
- relevant test metadata.

This approach is intended to ensure that future quantitative results are independently traceable and reusable.

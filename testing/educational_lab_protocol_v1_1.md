# Educational Lab Protocol v1.1

## Scope

This protocol is for supervised educational bench use. The open breadboard must not be attached to a person. ECG waveform activities use an ECG simulator. ADC-characterisation activities use an appropriate calibrated low-voltage source.

## Exercise A — staged subsystem bring-up

### Learning objective
Identify the signal chain, digital buses and storage pathway, and practise fault isolation by adding one subsystem at a time.

### Procedure
Follow `assembly/assembly_guide_v1_1.md` from the regulated rail through OLED, RTC, microSD and AD8232 bring-up.

### Expected observations
- stable verified 3.3 V rail;
- OLED startup/status display without analogue input;
- advancing RTC field;
- successful microSD initialisation and CSV header/file creation;
- raw ADC values at the AD8232 input path; and
- disconnected-lead/open-input status where implemented.

### Common problems
Swapped SDA/SCL, wrong microSD CS pin, missing common ground, incompatible microSD voltage levels, loose jumpers and unstable power.

## Exercise B — ECG simulator acquisition and plotting

### Learning objective
Acquire a known simulated ECG waveform, preserve raw data and distinguish qualitative morphology from calibrated measurement.

### Procedure
1. Confirm the AD8232 lead cable is not connected to a person.
2. Disconnect USB, charging and externally powered instruments from the lead interface.
3. Configure a suitable ECG simulator to a documented normal rhythm.
4. Attach compatible RA/LA/RL-style simulator terminals.
5. Record raw CSV data.
6. Preserve simulator make/model, settings, firmware tag/commit, software versions and run time.
7. Plot raw ADC counts versus sample index and/or logged elapsed time.
8. Annotate recurrent P-QRS-T-like morphology expected from the simulator without treating raw counts as calibrated physiological voltage.
9. Repeat one safe controlled fault condition, such as an open simulator lead, and document the status response.

### Expected observation
A periodic simulator-derived waveform with recurrent morphology consistent with the simulator setting.

### Common artefacts/problems
Lead-off, clipping/saturation, baseline shift, 50/60-Hz pickup, cable disturbance, poor ground and unstable breadboard contacts.

### Interpretation boundary
This exercise demonstrates simulator-waveform acquisition. It does not validate diagnostic accuracy or convert raw counts to physiological voltage.

## Exercise C — ESP32-C3 ADC characterisation

### Learning objective
Measure the board-specific relationship between a traceable input voltage and raw ADC counts rather than assuming a nominal conversion.

### Procedure
Perform with AD8232 OUT disconnected from GPIO0.

1. Select an ADC attenuation/input configuration appropriate for the planned safe voltage range.
2. Use a calibrated low-voltage source.
3. Apply multiple known voltage levels, including repeated points.
4. Record raw ADC counts at every level.
5. Fit count versus applied voltage.
6. Report slope, intercept, residuals and repeatability.
7. Record the ESP32-C3 board/device, ADC configuration, firmware/core version and calibration method.

### Expected observation
A monotonic board-specific transfer dataset over the tested input range.

### Common problems
Out-of-range input, incorrect attenuation, noisy source, missing common ground and assuming nominal Vref is a calibration result.

## Exercise D — timing and storage assessment

### Learning objective
Distinguish a code-defined scheduling interval from measured sampling/storage performance.

### Procedure
1. Log for a predefined duration.
2. Preserve timing fields with the raw file.
3. Calculate the effective sample interval/rate.
4. Identify unusually long intervals or discontinuities.
5. Repeat controlled microSD start/stop cycles.
6. Inspect every generated file and preserve the analysis code.

### Interpretation boundary
The firmware's 4000 microsecond schedule corresponds to a nominal 250 samples/s configuration. Measured rate, jitter and dropped-sample behaviour must be reported from the new dataset, not inferred from the code.

## Required reporting for new replication data

Preserve:
- raw CSV files;
- simulator make/model and settings;
- calibration-source details;
- firmware commit/tag;
- Arduino IDE and ESP32 core versions;
- exact external-library versions;
- acquisition conditions; and
- analysis scripts/notebooks.

## Evidence rule

Never fill missing historical measurements with simulated, image-derived or reconstructed numerical data. New quantitative claims must point to newly generated and preserved raw data.

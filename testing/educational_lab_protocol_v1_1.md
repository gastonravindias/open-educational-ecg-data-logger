# Educational Lab Protocol v1.1

## A. Subsystem bring-up
Follow the staged assembly guide and record a pass/fail checklist for each stage.

## B. ECG simulator acquisition
1. Confirm the AD8232 lead cable is not connected to a person.
2. Configure a suitable ECG simulator to a documented normal rhythm.
3. Attach compatible RA/LA/RL-style terminals.
4. Record raw CSV and preserve simulator make/model, settings, firmware tag, software versions and run time.
5. Plot raw ADC counts versus sample index and/or logged elapsed time.
6. Annotate recurrent P-QRS-T-like morphology expected from the simulator without treating raw counts as calibrated physiological voltage.
7. Repeat one safe controlled fault condition, such as an open simulator lead, and document the response.

## C. ESP32-C3 ADC characterisation
Perform with AD8232 OUT disconnected from GPIO0.
1. Use a calibrated low-voltage source compatible with the selected ADC attenuation/range.
2. Apply multiple known levels including repeated points.
3. Record raw counts.
4. Fit count versus applied voltage; report slope, intercept, residuals and repeatability.
5. Record ESP32-C3 device, attenuation, firmware/core version and calibration method.
6. Do not assume nominal Vref gives a calibrated voltage.

## D. Timing and storage
Log for a predefined duration, calculate effective sample interval/rate from retained timing fields, identify unusually long intervals, repeat controlled microSD start/stop cycles, and preserve raw files plus analysis code.

Never fill missing historical measurements with simulated or reconstructed numbers.

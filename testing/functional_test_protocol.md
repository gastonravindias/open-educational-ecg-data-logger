# Functional and quantitative test protocol

The original paper reports only retained qualitative evidence. Replicators can use this protocol to extend the evidence without changing the published limitation statement.

1. **Firmware startup:** record board, core and library versions.
2. **Sampling:** log at least 10 minutes and calculate effective rate, interval distribution and missed intervals.
3. **ADC scaling:** use known safe voltages or a calibrated source; do not exceed the board input range.
4. **Lead-off:** open each simulator lead and record status response.
5. **RTC:** compare elapsed time with a reference clock.
6. **SD:** perform ten start/stop cycles and a continuous logging run; inspect every file.
7. **Power:** record INA219 voltage/current/power under defined operating states.
8. **Solar extension:** measure panel and charge-path values only with a charger compatible with the panel and protected battery.
9. **ECG source:** use an ECG simulator for quantitative waveform tests.
10. **Reporting:** preserve raw CSV files and analysis scripts.

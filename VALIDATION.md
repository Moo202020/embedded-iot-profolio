# Validation record

## Completed in this package

- Host C++ tests: light timer at startup, motion refresh, exact timeout, zero timeout, unsigned clock rollover; distance threshold/hysteresis/invalid read; ADC conversion and UART parser overflow/CRLF.
- Automated scan compares packaged files against private connection values extracted from supplied source (values never logged).
- ZIP contents checked for private config files and build output.

## Not completed

- Arduino/ESP32 firmware compilation with vendor cores and installed libraries.
- Hardware upload, electrical measurements, sensor calibration and endurance testing.
- MQTT broker, Home Assistant, ThingSpeak and network outage testing on real devices.
- STM32 HAL build for a specific MCU; these sources are portable exercises, not a complete STM32 firmware project.

## Fill after bench testing

| Project | Board and core version | Library versions | Wiring checked | Compile | Hardware checks | Date |
| --- | --- | --- | --- | --- | --- | --- |
| ESP32 home lighting | Pending | Pending | Pending | Pending | Pending | — |
| Environmental monitor | Pending | Pending | Pending | Pending | Pending | — |
| Digital white stick | Pending | Pending | Pending | Pending | Pending | — |
| DHT11 basics | Pending | Pending | Pending | Pending | Pending | — |

Never replace Pending with Passed without performing the check.

# Digital white stick distance prototype

HAMK group work with Karim Ghosn, Mohsen Fadaee and Jack Awcock. Educational sensing prototype, not a validated assistive device.

`archive/Continuous_final.ino` retains supplied historical logic with connection literals removed. `DistanceMonitor/` is a new refactor. Original behaviour sounded above 150 mm; the refactor deliberately sounds at or below 150 mm and stops at or above 180 mm to demonstrate proximity warning with hysteresis. Do not present that change as the original behaviour.

## Hardware

Use a WiFiNINA-compatible board, a compatible VL53L0X breakout and a suitable piezo buzzer/driver. The original board model is not confirmed. A Nano 33 IoT is one possible target, but it is 3.3 V logic; breakout voltage compatibility and pin mapping must be checked.

| Function | Example connection |
| --- | --- |
| VL53L0X SDA/SCL | Board-labelled SDA/SCL pins |
| Sensor GND | Common ground |
| Sensor supply | Per breakout datasheet, compatible with board |
| Buzzer signal | Digital pin 9 through a suitable interface if needed |

Install **VL53L0X** by Pololu, **WiFiNINA**, and **ThingSpeak**. Open `DistanceMonitor/DistanceMonitor.ino`; copy `secrets.example.h` to `secrets.h` and set your private configuration. Enable field 8 in your own ThingSpeak channel. The default channel zero disables uploads. This reference uses the library's plain WiFiClient path; it is not a TLS-secured cloud implementation.

## Verification

- At startup check sensor detection and invalid-read reporting.
- Move a target through 150 mm and 180 mm and check hysteresis.
- Disconnect the sensor and confirm timeout reporting and silent output. A silent fault is NOT a fail-safe mobility warning.
- Confirm field 8 updates and inspect HTTP status; verify reconnect after Wi-Fi loss.
- Check that the buzzer remains responsive during cloud requests. The API can block; this design does not guarantee bounded alarm latency.

Status: host alarm logic tested; board compilation, range calibration and cloud/hardware validation pending.

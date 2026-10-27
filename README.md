# Embedded and IoT Portfolio — Mohsen Fadaee

Microcontroller applications, sensor integration and connected monitoring, based on my HAMK coursework and personal projects.

## Projects

| Folder | Content | Provenance and status |
| --- | --- | --- |
| [ESP32 home lighting](projects/esp32-home-lighting) | PIR input, four-minute off timer, MQTT state, Home Assistant configuration | New reference implementation of my described personal project; hardware verification pending |
| [Environmental monitoring](projects/arduino-environment-monitor) | DHT11, PIR, analogue light input, LCD, MQTT JSON | Sanitised supplied coursework plus a new refactored example |
| [Digital white stick](projects/digital-white-stick) | VL53L0X distance measurement, buzzer, ThingSpeak | HAMK group prototype plus a new refactored example |
| [DHT11 fundamentals](projects/arduino-dht11-basics) | Temperature/humidity acquisition and Serial output | Supplied coursework example |
| [STM32 foundations](projects/stm32-foundations) | Portable ADC conversion, UART line parser and STM32 integration checklist | New practice code; original STM32 lab sources were not supplied |

## What is original and what is new?

`archive/` folders contain supplied learning code, with connection details replaced by placeholders. They may include teaching material or group contributions. Refactored firmware, tests, CI and documentation were prepared with AI assistance in October 2026. They are current portfolio extensions, not evidence that these exact implementations were used in my earlier employment or studies. I will review and verify them on the target hardware before describing them as tested builds.

The digital white stick was a group project with Karim Ghosn and Jack Awcock. This repository does not claim sole authorship of that work. No university employment source code is included.

## Start here

1. Read a project's README and choose the actual board and sensor modules you own.
2. Install Arduino IDE and the board support package. Install the listed libraries through Library Manager.
3. Copy `secrets.example.h` to `secrets.h` beside the sketch where required. Keep the latter private.
4. Verify GPIO voltage, pin mapping and power supply against your hardware datasheets before connecting anything.
5. Compile, upload and follow the project's hardware test checklist. Record the result in [VALIDATION.md](VALIDATION.md).

Arduino IDE: open the `.ino` inside the folder with the same name, not an archive file.

## Run the host tests

Requires Python 3 and a C++17 compiler (`g++`, or set `CXX` to another compatible compiler):

```sh
python3 tools/run_tests.py
```

These tests exercise extracted application logic. They do not test real sensors, Wi-Fi, MQTT, TLS or board firmware compilation. GitHub Actions runs the same host tests on pushes and pull requests.

## Engineering notes

- Local control is evaluated before network work. Standard Arduino Wi-Fi/MQTT calls can still block briefly; this is not a hard real-time implementation.
- Raw analogue values are not calibrated lux measurements. The environmental example reports raw ADC values and a relative percentage.
- New MQTT examples are for a trusted local broker, not public internet deployment. Remote phone access should use your secured Home Assistant access solution, not port forwarding to an unencrypted broker.
- The white stick is an educational demonstrator, not a certified mobility or safety aid.
- GPIO outputs are intended for LEDs or a safe low-voltage interface. No mains wiring is specified.

## Background

BEng Electrical and Automation Engineering, HAMK. Professional experience includes robotic controller/sensor integration with ROS2, Python and C++, and building-system data monitoring. [LinkedIn](https://www.linkedin.com/in/mohsenfadaee/)

## Rights and attribution

No blanket open-source licence is assigned to historical coursework or group material. Retained library headers and dependencies have their own licences. Review team/course permissions before publishing shared source. See [PROVENANCE.md](PROVENANCE.md).

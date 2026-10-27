# Source provenance

| Supplied file | Destination | Treatment |
| --- | --- | --- |
| main.cpp | environmental monitor archive | Configuration literals sanitised; logic retained |
| new_arduinoFinal.ino | environmental monitor archive | Configuration literals sanitised; logic retained |
| Continuous_final.ino | digital white stick archive | Configuration literals sanitised; logic retained |
| Task4.ino | DHT11 sketch | Copied; introductory learning example |
| Task5_Start.ino | Not distributed | Incomplete teaching starter, not an independent finished project |
| cvc.odp | Not distributed | Source for group attribution and project context |
| aaaaaalcd3.png | docs/lcd-lab.jpg | Supplied photograph of LCD laboratory setup; supporting context, not proof of a networked system |
| arduino sensor.png | Not distributed | Third-party diagram depicts HC-SR04, not the VL53L0X used in the submitted code |

The original ESP32 home firmware and original STM32 laboratory sources were not supplied. The corresponding new code is labelled as a reference implementation or practice exercise. Professional robotics work is described only; no employer-owned code is reproduced.

Archive sanitisation replaces Wi-Fi names/passwords, broker names/topics and cloud channel/key literals. Historical blocking loops, unchecked reads and other limitations remain visible. Do not use archived sketches as production firmware.

New refactors are separate files. They adjust error handling, scheduling, retry behaviour and documentation; no claim is made that the changes have been tested on hardware.

# Connected environmental monitoring

Original HAMK learning code combines DHT11 temperature/humidity, PIR motion, an analogue light input, LCD feedback and Wi-Fi MQTT telemetry. Source files can include teaching/group contributions; see archive and provenance notes.

## Contents

- `archive/main.cpp`: supplied modular sensor acquisition and JSON publishing, sanitised.
- `archive/new_arduinoFinal.ino`: supplied LCD/LED implementation, sanitised.
- `EnvironmentMonitor/`: NEW refactor with DHT initialisation before reads, null/error reporting, bounded-interval retries, relative ADC reporting, and non-delay sampling.

The new example does not use ArduinoJson; it generates a fixed-schema JSON payload in a sized buffer. It targets a WiFiNINA-capable board with ArduinoMqttClient support, such as Nano 33 IoT. This is an example target; the original board is unconfirmed.

## Pin map

| Component | Example pin |
| --- | --- |
| DHT11 data | D2 |
| PIR output | D3 |
| Motion LED through resistor | D4 |
| Light sensor analogue output | A5 |
| LCD RS, EN, D4, D5, D6, D7 | D7, D8, D9, D10, D11, D12 |

Use common GND, compatible supply and logic voltages, appropriate pull-ups and an LCD contrast potentiometer. A 5 V LCD may require interface adaptation for a 3.3 V board. Do not infer voltage compatibility from this pin list.

Install **DHT sensor library** by Adafruit with **Adafruit Unified Sensor**, **WiFiNINA**, **ArduinoMqttClient**, and **LiquidCrystal**. Open `EnvironmentMonitor/EnvironmentMonitor.ino`; copy the example credentials header to `secrets.h`. Enter a trusted local MQTT broker, topic and login. Original archive main.cpp additionally used ArduinoJson and a different dht11 library; archived builds are not supported by this refactor's dependency list.

## Verify

Serial Monitor at 9600 baud and your MQTT subscriber should show temperature, humidity, motion, raw ADC and relative light percentage. This percentage may rise or fall with illumination depending on sensor wiring and is not calibrated lux. Check disconnecting DHT gives JSON nulls and `dht_valid:false`, not a stale value. Verify the LCD has no stale trailing characters, motion LED follows the PIR, and reconnect works after Wi-Fi/broker outages. On a shared network use broker authentication; public internet deployment requires a separate TLS implementation.

Status: refactor prepared; vendor-core compilation and hardware/network checks pending.

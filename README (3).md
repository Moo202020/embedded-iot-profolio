# ESP32 motion-controlled lighting

My described personal project turns room lighting on with PIR motion and off after four minutes without motion, with phone monitoring. This folder provides a NEW reference implementation of that behaviour; it is not a recovery of my original source. The Home Assistant/MQTT integration here is a new implementation choice, not a claim about the original cloud service.

## Hardware and setup

- Example target: classic ESP32 DevKit; adapt the pins for your actual module. ESP32 GPIO is 3.3 V logic.
- PIR OUT → GPIO27, GND → common GND; use a PIR supply and output level compatible with the board.
- GPIO26 → current-limited LED or appropriate low-voltage driver input. Never drive a relay coil or mains load directly from GPIO.
- Install Espressif ESP32 board support and **PubSubClient** by Nick O'Leary in Arduino IDE.
- Open `HomeLighting/HomeLighting.ino`. Copy `secrets.example.h` to `secrets.h` beside it and enter local Wi-Fi/broker configuration.
- Configure the same MQTT broker in Home Assistant and merge `home-assistant.yaml`. These are status sensors; remote output commands are intentionally not implemented.
- Use a secured Home Assistant remote-access method if phone access outside your LAN is required. The firmware's MQTT connection is unencrypted and intended only for an isolated trusted local network. It does not provide cloud TLS.

## Behaviour

Startup output is OFF. A HIGH PIR signal turns it on and refreshes the timer on each loop. After the last HIGH sample it stays on for 240,000 ms. The PIR's own hold time and warm-up behaviour affect the physical delay. Unsigned subtraction handles the millis counter wrapping as long as updates continue regularly. MQTT reconnect attempts use intervals; individual networking library calls can still block and should be measured on hardware.

## Bench checklist

1. Start with an LED only. Verify OFF at boot and ON on motion.
2. Set the PIR to a short hardware hold time. Check OFF four minutes after its output returns LOW.
3. Trigger motion again before timeout and verify the countdown refreshes.
4. Disconnect Wi-Fi and verify local control continues; reconnect and check updated status.
5. Stop the broker; verify recovery and availability behaviour. Check the dashboard after a device power loss.
6. Verify your actual active-high/active-low output interface before attaching any load.

Status: host timer tests supplied; ESP32 compilation, Home Assistant integration and hardware tests pending.

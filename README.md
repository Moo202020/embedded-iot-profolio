# DHT11 fundamentals

Supplied introductory HAMK coursework, kept as a small historical example. Uses the Adafruit DHT sensor library and its Adafruit Unified Sensor dependency. Open `Dht11Basics/Dht11Basics.ino` in Arduino IDE. Select your actual board.

## Wiring

DHT11 data → digital pin 2; sensor GND → board GND; sensor supply → a compatible supply according to your module datasheet. A bare sensor needs the specified data pull-up; many breakout modules already include it. Respect the selected board's logic voltage.

## Verify

Serial Monitor at 9600 baud should show temperature and humidity. Disconnect data and observe the failure behaviour. This historical example does not check NaN values and uses a blocking one-second delay; the newer environmental example addresses these concerns.

Status: source retained; board compilation and bench tests pending.

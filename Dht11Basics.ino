// Used libraries
#include <DHT.h>        // DHT sensor library by Adafruit ver. 1.3.10

// Variable for the measurements
float fTemp, fHum;

unsigned long int CurrenrMillis;

// Sensor definitions.
#define DHT11Pin 2
#define TEMPTYPE 0
DHT dht(DHT11Pin, DHT11);

void setup()
{
  // Activate serial port
  Serial.begin(9600);
  // Init sensor connection
  dht.begin();                     
}

void loop()
{
  fTemp = dht.readTemperature(TEMPTYPE); // Read temperature
  fHum = dht.readHumidity();             // Read humidity

  Serial.print("Temperature: ");
  Serial.print(fTemp);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(fHum);
  Serial.println(" %\n");
  delay(1000);
}

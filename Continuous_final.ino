// Sanitised historical coursework. See PROVENANCE.md.
// Used libraries
#include <DHT.h>        // DHT sensor library by Adafruit ver. 1.3.10
#include <ThingSpeak.h> // ThingSpeak library by MathWorks ver 1.5.0
#include <WiFiNINA.h>   // WiFiNINA library by Arduino ver 1.7.0
#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

// Variable for the measurements
float fDis;

// Sensor definitions.
#define DHTSDA
#define DISTANCE

VL53L0X sensor;
const int buzzer = 9; //buzzer to arduino pin 9


// WiFi Account and client
const char ssid[] = "REPLACE_IN_PRIVATE_CONFIG";
const char pass[] = "REPLACE_IN_PRIVATE_CONFIG";
WiFiClient net;

// ThingSpeak keys
const char *writeAPIKey = "REPLACE_IN_PRIVATE_CONFIG";
unsigned long myChannelNbr = 0;


// Check if WiFi connected
void TestWiFiConnection()
{
    // Check if connection, if not renew
    char WiFiStatus = WiFi.status();
    if (WiFiStatus == WL_CONNECTION_LOST || WiFiStatus == WL_DISCONNECTED || WiFiStatus == WL_SCAN_COMPLETED) 
    {
      WiFi.end();
      delay(5000);
      WiFi.begin(ssid, pass);
      WiFiConnect();          //if my SSID is present, connect
    }
}
  
void WiFiConnect()
{
    while (WiFi.status() != WL_CONNECTED)
    {
      if (WiFi.status() == WL_DISCONNECTED)
      {
        WiFi.end();
      }
      if (WiFi.status() == WL_IDLE_STATUS)
      {
        WiFi.begin(ssid, pass);
      }
      // Blink LED
      if( digitalRead(LED_BUILTIN) )
          digitalWrite(LED_BUILTIN, LOW);
      else
          digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
    }
    // LED on when connection
    digitalWrite(LED_BUILTIN, HIGH);
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();

   pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  
  if (!sensor.init())
  {
    Serial.println("Sensor init fail");
  }
  sensor.setTimeout(500);

  sensor.startContinuous();
  
// Set Build-In LED active, LED on, if WiFi connection ok, blink if not
  pinMode(LED_BUILTIN, OUTPUT);
  // Connect WiFi
  WiFi.begin(ssid, pass);
  WiFiConnect();
  // Init ThingSpeak connection.
  ThingSpeak.begin(net);
 
  
}


void loop()
{
  fDis = sensor.readRangeContinuousMillimeters();       // Read Distance
  Serial.print(fDis);
  if ((fDis) > 150) {tone(buzzer, 500); // Send 1KHz sound signal...
  delay(1); }        // ...for 1 sec
  if ((fDis) < 150) {noTone(buzzer);     // Stop sound...
  delay(1);        // ...for 1sec
  }
  TestWiFiConnection();                                // Test WiFi connection.
  ThingSpeak.setField(8,fDis);                       // Set data field 8 
  ThingSpeak.writeFields(myChannelNbr,writeAPIKey); // Send data to ThingSpeak format)
  delay(10);   
}

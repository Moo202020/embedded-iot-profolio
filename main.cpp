// Sanitised historical coursework. See PROVENANCE.md.
#include <Arduino.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include "dht11.h"

#define LIGHT_SENSOR_PIN A5
#define DHT_PIN 2
#define MOTION_SENSOR_PIN 7

//char SSID[] = "REPLACE_IN_PRIVATE_CONFIG";
//char PASSWD[] = "REPLACE_IN_PRIVATE_CONFIG";

//---------------Wi-Fi Parameters---------------
char SSID[] = "REPLACE_IN_PRIVATE_CONFIG";
char PASSWD[] = "REPLACE_IN_PRIVATE_CONFIG";
//---------------MQTT Parameters---------------
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
char broker[] = "REPLACE_IN_PRIVATE_CONFIG";
char topic[] = "REPLACE_IN_PRIVATE_CONFIG";
int port = 1883;
//---------------Global vars---------------
dht11 dhtSensor;
//Struct where all the sensor data will be stored
struct sensorsData
{
  float temp;
  float humid;
  float lux;
  int motion;
}sensorsData;

//Get the lux data from sensor
void GetLux()
{
  float res = analogRead(LIGHT_SENSOR_PIN);
  if (res>1000.0)
    res = 1000.0;
  //The data comes in the 0-1000 range, but the sensor can sense between 1-6000 lux,
  //thus, we should readjust the data with :
  sensorsData.lux = (((5999.0/1000.0)*res)+1.0);
}

//Get data from the dht sensor
void GetDHTData()
{
  int err = dhtSensor.read(DHT_PIN);
  if( err != DHTLIB_OK)
  {
    Serial.print(err);
    Serial.println("Error reading DHT sensor");
    return;
  }
  sensorsData.humid = dhtSensor.humidity;
  sensorsData.temp = dhtSensor.temperature;
}

//Get motion data (1 or 0)
void GetMotion()
{
  sensorsData.motion = digitalRead(MOTION_SENSOR_PIN);
}

//Send the data structure to our mqtt server
void SendDataToBroker()
{
  StaticJsonDocument<1024> jsonDoc; //Create a json document object
  //---------------Fill the json with needed items---------------
  jsonDoc["sens_temperature"] = sensorsData.temp;
  jsonDoc["sens_humidity"] = sensorsData.humid;
  jsonDoc["sens_lux"] = sensorsData.lux;
  jsonDoc["sens_presence"] = sensorsData.motion;
  jsonDoc["ID"] = "HAMK_GROUP_E";
  jsonDoc["message"] = "Bonjour =)";
  //---------------Print and send the json doc to the mqtt server---------------
  Serial.println(jsonDoc.as<String>());
  mqttClient.beginMessage(topic);
  mqttClient.print(jsonDoc.as<String>());//The json doc should be send as a string
  mqttClient.endMessage();
}

void setup() 
{  
  Serial.begin(9600);
  //---------------Connect to Wi-Fi---------------
  while (WiFi.begin(SSID, PASSWD) != WL_CONNECTED)
  {
    Serial.print("Attempting to connect...");
    delay(1000);
  }
  Serial.println("Connected to WiFi");
  //---------------Set pins mode---------------
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  //---------------Connect to mqtt server---------------
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    Serial.println("Program will hold, press the reset button to restart");
    while (1);
  }
}

void loop() {
  GetLux();
  GetMotion();
  GetDHTData();
  Serial.println("---------------------------------");
  Serial.print("Lux : ");
  Serial.println(sensorsData.lux);
  Serial.print("Temp : ");
  Serial.println(sensorsData.temp);
  Serial.print("Humid : ");
  Serial.println(sensorsData.humid);
  Serial.print("Movement : ");
  Serial.println(sensorsData.motion);

  SendDataToBroker();  

  delay(2000);
}

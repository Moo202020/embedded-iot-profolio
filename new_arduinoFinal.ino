// Sanitised historical coursework. See PROVENANCE.md.
// Used libraries
#include <DHT.h>        // DHT sensor library by Adafruit ver. 1.3.10
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h> 
#include <Wire.h>

#define MOTION_SENSOR_PIN 3
#define LIGHT_SENSOR_PIN A5
#define DHT11_PIN 2


float fTem;
float fHum;
int motion;
int light_value;
float light;

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

 int Movment_Led = 4;
 int pirPin = 3;                // PIR Out pin 
 int pirStat = 0;               // PIR status
 int light_Led = 13;


//--------Struct where all the sensor data will be stored-----
struct sensorsData
{
  float fTem;
  float fHum;
  int motion;
  int light_value;
  float light;
  int value = 0;
  int pirState = LOW;
 
}sensorsData;
//--------------------------------------------------------------
unsigned long int CurrenrMillis;
const int pir_output = 4;


//------------- Sensor definitions-------------
#define DHT11Pin 2
#define TEMPTYPE 0
DHT dht(DHT11Pin, DHT11);

//---------------Wi-Fi Parameters---------------
char SSID[] = "REPLACE_IN_PRIVATE_CONFIG";
char PASSWD[] = "REPLACE_IN_PRIVATE_CONFIG";

//---------------MQTT Parameters---------------
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
char broker[] = "REPLACE_IN_PRIVATE_CONFIG";
char topic[] = "REPLACE_IN_PRIVATE_CONFIG";
int port = 1883;
//----------------------------------------------

void setup(){ 
  pinMode(pir_output, INPUT);
  pinMode(Movment_Led, OUTPUT);     
  pinMode(pirPin, INPUT);
  pinMode(light_Led, OUTPUT);
  lcd.begin(16,2);

  // Activate serial port
  Serial.begin(9600);

  fTem = dht.readTemperature(TEMPTYPE); // Read temperature
  fHum = dht.readHumidity();

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
  pinMode(pir_output, INPUT);
  pinMode(Movment_Led, OUTPUT);
  
  //---------------Connect to mqtt server---------------
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    Serial.println("Program will hold, press the reset button to restart");
    while (1);
  }

//int light_value = analogRead(LIGHT_SENSOR_PIN);
  //light = light_value * 0.0976;// percentage calculation 

  //if (digitalRead(pir_output) == HIGH) {
    //Serial.println("HIGH");
  //}
  //else {
   //Serial.println("LOW");
  //}
  
  // Init sensor connection
  dht.begin();

  pinMode(LIGHT_SENSOR_PIN, INPUT); //data pin for ambientlight sensor
  pinMode(13, OUTPUT);

  fTem = dht.readTemperature(TEMPTYPE); // Read temperature
  fHum = dht.readHumidity();
}
//--------------Get motion data (1 or 0)-------------
void GetMotion()
{
  sensorsData.motion = digitalRead(MOTION_SENSOR_PIN);
}

//------Send the data structure to our mqtt server
void SendDataToBroker()
{
  StaticJsonDocument<1024> jsonDoc; //Create a json document object
//---------------Fill the json with needed items---------------
  jsonDoc["Temperature"] = fTem;
  jsonDoc["humidity"] = fHum;
  jsonDoc["Movement"] = sensorsData.motion;
  jsonDoc["LightLevel"] = light;
  jsonDoc["ID"] = "HAMK_VA_320";
  jsonDoc["message"] = "Hoooooooooooray =)";
//---------------Print and send the json doc to the mqtt server---------------
 // Serial.println(jsonDoc.as<String>());
  mqttClient.beginMessage(topic);
  mqttClient.print(jsonDoc.as<String>());//The json doc should be send as a string
  mqttClient.endMessage();
}

void loop()
{
  fTem = dht.readTemperature(TEMPTYPE); // Read temperature
  fHum = dht.readHumidity();             // Read humidity
  GetMotion();

//--------------------------------  
  int light_value = analogRead(LIGHT_SENSOR_PIN);
  light = light_value * 0.0976;// percentage calculation 

  if (light_value > 100) {
    digitalWrite(light_Led, HIGH);
  }
  else {digitalWrite(light_Led,LOW);}


  //if (digitalRead(pir_output) == HIGH) {
   // Serial.println("Value: HIGH");
  //}
  //else {
   //Serial.println("Value: LOW");
  //}
  delay(1);

  pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(Movment_Led, HIGH);  // turn LED ON
   //Serial.println("\n Hey I got you!!! \n");
 } 
 else {
   digitalWrite(Movment_Led, LOW); // turn LED OFF if we have no motion
 }

   
//________________Serial.println(light);
  delay(100);
  if (light_value > 1000) {
    digitalWrite(light_Led, HIGH);
  }
  else {
    digitalWrite(light_Led, LOW);
  }


  Serial.println("---------------------------------");
  Serial.print("Movement : ");
  Serial.println(sensorsData.motion);
  Serial.print("Temperature: ");
  Serial.print(fTem);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(fHum);
  Serial.println(" %\n");
  Serial.print("light Value: ");
  Serial.println(light);
  Serial.println("\n Hey I got you!!! \n");


  lcd.setCursor(0,0);
  lcd.println("T:C");
  lcd.setCursor(2,0);
  lcd.print(fTem);
  lcd.setCursor(7,0);
  lcd.println("C");
  lcd.setCursor(8,0);
  lcd.println(" ");
  lcd.setCursor(9,0);
  lcd.print("MOVE:0");
  lcd.setCursor(15,0);
  lcd.println(sensorsData.motion);
  lcd.setCursor(0,1);
  lcd.println("H:%");
  lcd.setCursor(3,1);
  lcd.print(fHum);
  lcd.setCursor(9,1);
  lcd.print("V:%");
  lcd.setCursor(12,1);
  lcd.println(light);

  delay(1000);

  SendDataToBroker();
  
  delay(3000);
}

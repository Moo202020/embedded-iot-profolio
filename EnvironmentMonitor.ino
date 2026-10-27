// New reference refactor of supplied learning examples.
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <math.h>
#include "secrets.h"
constexpr int DHT_PIN=2,PIR_PIN=3,LIGHT_PIN=A5,MOTION_LED=4;
constexpr int ADC_MAX=1023; // Default 10-bit assumption; verify actual setup.
DHT dht(DHT_PIN,DHT11);
LiquidCrystal lcd(7,8,9,10,11,12);
WiFiClient network;
MqttClient mqtt(network);
uint32_t lastSample=0,lastWifi=0,lastMqtt=0;
void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN,INPUT); pinMode(LIGHT_PIN,INPUT); pinMode(MOTION_LED,OUTPUT);
  dht.begin(); lcd.begin(16,2);
  mqtt.setId(MQTT_CLIENT_ID);
  mqtt.setUsernamePassword(MQTT_USER,MQTT_PASSWORD);
  mqtt.setConnectionTimeout(1000);
}
void loop() {
  uint32_t now=millis();
  bool motion=digitalRead(PIR_PIN)==HIGH;
  digitalWrite(MOTION_LED,motion?HIGH:LOW);
  bool connected=WiFi.status()==WL_CONNECTED;
  if (!connected && uint32_t(now-lastWifi)>=15000) {
    lastWifi=now; WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  }
  if (connected && !mqtt.connected() && uint32_t(now-lastMqtt)>=5000) {
    lastMqtt=now; mqtt.connect(MQTT_HOST,MQTT_PORT);
  }
  if (mqtt.connected()) mqtt.poll();
  if (uint32_t(now-lastSample)<2500) return;
  lastSample=now;
  float temp=dht.readTemperature(), humidity=dht.readHumidity();
  int raw=analogRead(LIGHT_PIN);
  int relative=constrain(raw,0,ADC_MAX)*100/ADC_MAX;
  bool valid=!isnan(temp) && !isnan(humidity);
  char payload[192], line[17];
  if (valid) {
    snprintf(payload,sizeof(payload),"{\"temperature_c\":%.1f,\"humidity_pct\":%.1f,\"motion\":%s,\"light_adc\":%d,\"light_relative_pct\":%d,\"dht_valid\":true}",temp,humidity,motion?"true":"false",raw,relative);
    snprintf(line,sizeof(line),"T:%4.1f H:%4.1f",temp,humidity);
  } else {
    snprintf(payload,sizeof(payload),"{\"temperature_c\":null,\"humidity_pct\":null,\"motion\":%s,\"light_adc\":%d,\"light_relative_pct\":%d,\"dht_valid\":false}",motion?"true":"false",raw,relative);
    snprintf(line,sizeof(line),"DHT read error");
  }
  lcd.setCursor(0,0); lcd.print("                "); lcd.setCursor(0,0); lcd.print(line);
  snprintf(line,sizeof(line),"M:%d Light:%3d%%",motion?1:0,relative);
  lcd.setCursor(0,1); lcd.print("                "); lcd.setCursor(0,1); lcd.print(line);
  Serial.println(payload);
  if (mqtt.connected()) {
    mqtt.beginMessage(MQTT_TOPIC);
    mqtt.print(payload);
    if (!mqtt.endMessage()) Serial.println("MQTT publish failed");
  }
}

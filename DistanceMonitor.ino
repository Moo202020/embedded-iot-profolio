// New reference refactor. The original group implementation is in archive/.
#include <Wire.h>
#include <VL53L0X.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include "secrets.h"
#include "DistanceAlarm.h"
constexpr int BUZZER_PIN=9;
VL53L0X sensor;
WiFiClient network;
DistanceAlarm alarm;
bool sensorReady=false;
uint32_t lastRead=0,lastCloud=0,lastWifi=0;
void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN,OUTPUT); noTone(BUZZER_PIN);
  Wire.begin();
  sensor.setTimeout(100);
  sensorReady=sensor.init();
  if (sensorReady) sensor.startContinuous(50);
  else Serial.println("Sensor init failed; reset after checking wiring");
  ThingSpeak.begin(network);
}
void loop() {
  uint32_t now=millis();
  if (!sensorReady) return;
  if (uint32_t(now-lastRead)<100) return;
  lastRead=now;
  uint16_t mm=sensor.readRangeContinuousMillimeters();
  bool valid=!sensor.timeoutOccurred() && mm>0 && mm<8190;
  if (alarm.update(mm,valid)) tone(BUZZER_PIN,500);
  else noTone(BUZZER_PIN);
  if (!valid) { Serial.println("Distance invalid or timed out"); return; }
  Serial.println(mm);
  if (WiFi.status()!=WL_CONNECTED) {
    if (uint32_t(now-lastWifi)>=15000) {
      lastWifi=now; WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    }
    return;
  }
  // 20 s spacing avoids rapid repeated cloud writes. Networking can block.
  if (THINGSPEAK_CHANNEL!=0 && uint32_t(now-lastCloud)>=20000) {
    lastCloud=now;
    ThingSpeak.setField(8,static_cast<int>(mm));
    int status=ThingSpeak.writeFields(THINGSPEAK_CHANNEL,THINGSPEAK_WRITE_KEY);
    Serial.print("ThingSpeak HTTP status: "); Serial.println(status);
  }
}

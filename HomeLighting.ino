// New reference implementation, not the original home installation firmware.
#include <WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"
#include "LightController.h"
constexpr int PIR_PIN=27, OUTPUT_PIN=26; // ESP32 DevKit example; verify your board.
constexpr bool ACTIVE_HIGH=true;
WiFiClient network;
PubSubClient mqtt(network);
LightController light;
uint32_t wifiAttempt=0, mqttAttempt=0, lastPublish=0;
bool publishPending=true;
void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, ACTIVE_HIGH ? LOW : HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  mqtt.setServer(MQTT_HOST,MQTT_PORT);
  mqtt.setSocketTimeout(1);
  mqtt.setKeepAlive(20);
}
void loop() {
  uint32_t now=millis();
  bool motion=digitalRead(PIR_PIN)==HIGH;
  bool old=light.on();
  bool on=light.update(now,motion);
  digitalWrite(OUTPUT_PIN,(on==ACTIVE_HIGH) ? HIGH : LOW);
  if (old!=on) publishPending=true;
  if (WiFi.status()!=WL_CONNECTED) {
    if (uint32_t(now-wifiAttempt)>=15000) {
      wifiAttempt=now; WiFi.reconnect();
    }
    return; // The local timer keeps working without Wi-Fi.
  }
  if (!mqtt.connected()) {
    if (uint32_t(now-mqttAttempt)<5000) return;
    mqttAttempt=now;
    if (mqtt.connect(MQTT_CLIENT_ID,MQTT_USER,MQTT_PASSWORD,
                     TOPIC_AVAILABLE,0,true,"offline")) {
      mqtt.publish(TOPIC_AVAILABLE,"online",true);
      publishPending=true;
    }
    return;
  }
  mqtt.loop();
  if (publishPending || uint32_t(now-lastPublish)>=5000) {
    char payload[80];
    snprintf(payload,sizeof(payload),"{\"light\":\"%s\",\"motion\":%s}",
             on?"ON":"OFF",motion?"true":"false");
    if (mqtt.publish(TOPIC_STATE,payload,true)) {
      lastPublish=now; publishPending=false;
    }
  }
}

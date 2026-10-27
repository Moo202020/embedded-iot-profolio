#pragma once
// Copy to secrets.h. Local trusted broker only. Do not commit real values.
constexpr char WIFI_SSID[] = "YOUR_WIFI_NAME";
constexpr char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";
constexpr char MQTT_HOST[] = "192.168.1.20";
constexpr unsigned short MQTT_PORT = 1883;
constexpr char MQTT_USER[] = "YOUR_LOCAL_MQTT_USER";
constexpr char MQTT_PASSWORD[] = "YOUR_LOCAL_MQTT_PASSWORD";
constexpr char MQTT_CLIENT_ID[] = "mohsen-room-light-01";
constexpr char TOPIC_STATE[] = "mohsen/room-light/state";
constexpr char TOPIC_AVAILABLE[] = "mohsen/room-light/availability";

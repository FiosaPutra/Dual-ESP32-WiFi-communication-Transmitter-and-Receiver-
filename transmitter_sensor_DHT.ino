#include <WiFi.h>
#include "DHT.h"

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverAddress = "192.168.0.180";
const int serverPort = 4080;

WiFiClient TCPclient;

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastSend = 0;
const unsigned long interval = 2000; // kirim tiap 2 detik

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 TCP CLIENT - DHT11");

  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  connectToServer();
}

void loop() {
  // reconnect TCP kalau putus
  if (!TCPclient.connected()) {
    Serial.println("Disconnected from server, reconnecting...");
    TCPclient.stop();
    connectToServer();
  }

  // kirim data tiap interval
  if (millis() - lastSend >= interval) {
    lastSend = millis();

    float hum = dht.readHumidity();
    float temp = dht.readTemperature(); // Celsius

    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // format data
    String data = "TEMP=" + String(temp, 1) + ",HUM=" + String(hum, 1);

    TCPclient.println(data);
    TCPclient.flush();

    Serial.println("Sent: " + data);
  }
}

void connectToServer() {
  if (TCPclient.connect(serverAddress, serverPort)) {
    Serial.println("Connected to TCP server");
  } else {
    Serial.println("Failed to connect to TCP server");
  }
}

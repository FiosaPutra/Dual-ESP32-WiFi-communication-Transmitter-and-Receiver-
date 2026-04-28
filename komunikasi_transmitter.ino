#include <WiFi.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverAddress = "192.168.0.180"; // IP ESP32 SERVER
const int serverPort = 4080;

WiFiClient TCPclient;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 TCP CLIENT - SERIAL INPUT");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Connect to TCP Server
  connectToServer();
}

void loop() {
  // Reconnect if disconnected
  if (!TCPclient.connected()) {
    Serial.println("Disconnected from server, reconnecting...");
    TCPclient.stop();
    connectToServer();
  }

  // Check serial input
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // baca sampai ENTER
    data.trim(); // buang spasi & newline

    if (data.length() > 0) {
      TCPclient.println(data);  // kirim string
      TCPclient.flush();
      Serial.println("Sent: " + data);
    }
  }
}

void connectToServer() {
  if (TCPclient.connect(serverAddress, serverPort)) {
    Serial.println("Connected to TCP server");
  } else {
    Serial.println("Failed to connect to TCP server");
  }
}

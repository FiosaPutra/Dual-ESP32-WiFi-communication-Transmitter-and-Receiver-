#include <WiFi.h>

#define LED_PIN  18
#define SERVER_PORT 4080

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer TCPserver(SERVER_PORT);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("ESP32 TCP SERVER - STRING RECEIVER");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  Serial.print("Server IP: ");
  Serial.println(WiFi.localIP());

  TCPserver.begin();
}

void loop() {
  WiFiClient client = TCPserver.available();

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        // INI BLOK RECEIVER STRING
        String command = client.readStringUntil('\n'); //menerima data string
        command.trim();

        Serial.print("Received: ");
        Serial.println(command);

        // Contoh parsing command
        if (command == "ON") {
          digitalWrite(LED_PIN, HIGH);
        }
        else if (command == "OFF") {
          digitalWrite(LED_PIN, LOW);
        }
        else {
          Serial.println("Unknown command");
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

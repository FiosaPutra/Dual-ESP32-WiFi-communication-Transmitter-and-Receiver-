#include <WiFi.h>

#define LED_PIN  18
#define SERVER_PORT 4080

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer TCPserver(SERVER_PORT);

float temperature = 0.0;
float humidity = 0.0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("ESP32 TCP SERVER - SENSOR RECEIVER");

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

        String data = client.readStringUntil('\n');
        data.trim();

        Serial.print("Raw data: ");
        Serial.println(data);

        // contoh data: TEMP=29.5,HUM=68.2
        int tIndex = data.indexOf("TEMP=");
        int hIndex = data.indexOf("HUM=");

        if (tIndex != -1 && hIndex != -1) {
          String tempStr = data.substring(tIndex + 5, data.indexOf(",", tIndex));
          String humStr  = data.substring(hIndex + 4);

          temperature = tempStr.toFloat();
          humidity    = humStr.toFloat();

          Serial.print("Temperature: ");
          Serial.print(temperature);
          Serial.println(" C");

          Serial.print("Humidity: ");
          Serial.print(humidity);
          Serial.println(" %");

          // contoh logika
          if (temperature > 30.0) {
            digitalWrite(LED_PIN, HIGH);
          } else {
            digitalWrite(LED_PIN, LOW);
          }
        }
        else {
          Serial.println("Invalid data format");
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

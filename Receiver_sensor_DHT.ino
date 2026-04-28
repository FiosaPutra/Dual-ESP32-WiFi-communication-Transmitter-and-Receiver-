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
  // 1. Cek apakah ada client yang mencoba terhubung
  WiFiClient client = TCPserver.available();

  if (client) {
    Serial.println(">>> Client Terdeteksi!"); 

    // 2. Gunakan loop yang lebih kuat untuk menjaga koneksi
    while (client.connected() || client.available()) { 
      
      // 3. Jika ada data yang masuk ke buffer
      if (client.available() > 0) {
        String data = client.readStringUntil('\n'); // Membaca sampai newline
        data.trim(); // Bersihkan karakter aneh

        if (data.length() > 0) {
          Serial.print("Data Berhasil Diterima: ");
          Serial.println(data);

          // PROSES PARSING
          int tIndex = data.indexOf("TEMP=");
          int hIndex = data.indexOf("HUM=");

          if (tIndex != -1 && hIndex != -1) {
            String tempStr = data.substring(tIndex + 5, data.indexOf(",", tIndex));
            String humStr  = data.substring(hIndex + 4);

            temperature = tempStr.toFloat();
            humidity    = humStr.toFloat();

            Serial.printf("Suhu: %.1f C | Kelembapan: %.1f %%\n", temperature, humidity);

            if (temperature > 30.0) digitalWrite(LED_PIN, HIGH);
            else digitalWrite(LED_PIN, LOW);
          }
        }
      }
      delay(1); // Jeda sangat singkat agar tidak membebani CPU
    }

    // 4. Tutup koneksi setelah client selesai mengirim
    client.stop();
    Serial.println("<<< Client Terputus");
  }
}
    Serial.println("<<< Client Terputus");
  }
}

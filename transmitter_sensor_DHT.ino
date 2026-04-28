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

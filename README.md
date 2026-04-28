# Dual-ESP32-WiFi-communication-Transmitter-and-Receiver-

# Komunikasi WiFi Point-to-Point menggunakan ESP32

Proyek ini mendemonstrasikan cara membangun komunikasi nirkabel antara dua perangkat ESP32 menggunakan protokol WiFi (Mode Access Point & Station). Proyek ini dirancang sebagai modul praktikum untuk mempelajari dasar-dasar perangkat *embedded* dan IoT.

## 🚀 Kompetensi
- Memprogram perangkat *embedded* menggunakan ESP32 dan Arduino IDE.
- Mengimplementasikan komunikasi WiFi pada ESP32 sebagai **Transmitter** (Pengirim) dan **Receiver** (Penerima).

## 🛠️ Alat dan Bahan

| Komponen | Jumlah |
| :--- | :--- |
| ESP32 | 1 Unit (per node) |
| Resistor 470 Ohm | 1 buah |
| LED | 1 buah |
| Breadboard | 1 buah |
| Kabel Jumper | Secukupnya |

## 📖 Dasar Teori Singkat
ESP32 adalah mikrokontroler dengan WiFi dan Bluetooth terintegrasi. Dalam proyek ini, kita menggunakan dua mode utama:
1. **Access Point (AP) Mode:** ESP32 membuat jaringan sendiri (bertindak sebagai pusat/penerima).
2. **Station (STA) Mode:** ESP32 terhubung ke jaringan yang ada (bertindak sebagai pengirim).

## 🔧 Konfigurasi Pin (Receiver)

| Komponen | Pin ESP32 |
| :--- | :--- |
| LED (+) | GPIO 2 (atau sesuai kode) melalui Resistor |
| LED (-) | GND |

## 💻 Cara Penggunaan
1. **Persiapan:** Pastikan Arduino IDE sudah terinstal *board* ESP32.
2. **Upload Receiver:** Buka file program receiver, lalu upload ke ESP32 yang memiliki rangkaian LED. ESP32 ini akan memancarkan sinyal WiFi.
3. **Upload Transmitter:** Upload program transmitter ke ESP32 lainnya.
4. **Monitoring:** 
   - Buka Serial Monitor (Baud rate: 115200).
   - Ketik pesan pada Serial Monitor di sisi Transmitter.
   - Pesan akan terkirim dan muncul di Serial Monitor Receiver, serta memicu indikator LED.

## ⚠️ Keselamatan Kerja
- Pastikan rangkaian benar sebelum menghubungkan ke sumber tegangan.
- Bekerja pada area yang kering dan bebas dari benda logam yang dapat menyebabkan korsleting.
- Periksa kembali tegangan kerja (3.3V untuk GPIO ESP32).

---
*Proyek ini dibuat untuk tujuan edukasi dalam pemahaman perangkat IoT.*

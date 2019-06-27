#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

byte indikator = 13;

byte sensorInt = 5; 
byte flowsensor = 2;

float konstanta = 4.5; //konstanta flow meter

volatile byte pulseCount;

float debit;
unsigned int flowmlt;
unsigned long totalmlt;

unsigned long oldTime;

#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;
HTTPClient http;

String url = "http://192.168.0.139/project/dariArduino.php?variabel=";

String payload;
void pulseCounter()
{
pulseCount++;
}
void setup() {
  
  
  Serial.begin(9600);
  pinMode(indikator, OUTPUT);
  digitalWrite(indikator, HIGH); 
  
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH);
  
  pulseCount = 0;
  debit = 0.0;
  flowmlt = 0;
  totalmlt = 0;
  oldTime = 0;
  
  attachInterrupt(sensorInt, pulseCounter, FALLING);
  USE_SERIAL.setDebugOutput(false);

   for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] Tunggu %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
 
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Router Lantai 1", "xxx"); 

  
}

void loop() {
    if((millis() - oldTime) > 1000) 
  { 
  detachInterrupt(sensorInt);
  debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
  oldTime = millis();
  flowmlt = (debit / 60) * 1000;
  totalmlt += flowmlt;
  
  unsigned int frac;
  
  Serial.print("Debit air: ");
  Serial.print(int(debit));
  Serial.print("L/min");
  Serial.print("\t");
  
  Serial.print("Volume: "); 
  Serial.print(totalmlt);
  Serial.println("mL"); 
  
  pulseCount = 0;
  
  attachInterrupt(sensorInt, pulseCounter, FALLING);
  debit= int(debit);
  }

   // Cek apakah statusnya sudah terhubung
    if((WiFiMulti.run() == WL_CONNECTED)) {
 
        // Tambahkan nilai suhu pada URL yang sudah kita buat
        USE_SERIAL.print("[HTTP] Memulai...\n");
        http.begin( url + (String) debit + "&nilai=" + totalmlt ); 
        
        // Mulai koneksi dengan metode GET
        USE_SERIAL.print("[HTTP] Melakukan GET ke server...\n");
        int httpCode = http.GET();
 
        // Periksa httpCode, akan bernilai negatif kalau error
        if(httpCode > 0) {
            
            // Tampilkan response http
            USE_SERIAL.printf("[HTTP] kode response GET: %d\n", httpCode);
 
            // Bila koneksi berhasil, baca data response dari server
            if(httpCode == HTTP_CODE_OK) {
                payload = http.getString();
                USE_SERIAL.println(payload);
            }
 
        } else {
 
            USE_SERIAL.printf("[HTTP] GET gagal, error: %s\n", http.errorToString(httpCode).c_str());
        }
 
        http.end();
    }
 
    delay(5000);
}



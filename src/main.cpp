#include "Arduino.h"

#include <CustomWiFiManager.h>
#include <CustomWiFiClient.h>
#include <DHT.h>
#include <Blink.h>

// zvoleni typu senzoru
#define DHTTYPE DHT22      // DHT 22 (AM2302), AM2321

// inicializace DHT sensoru
const int DHTPin = 5;   // D1
DHT dht(DHTPin, DHTTYPE);

const long DEEP_SLEEP_TIME = 15*60*1000000; // 15 minut

const int LED_PIN = 14;   // D5
Blink blinker(LED_PIN);

// zasilani informaci do cloudu
CustomWiFiClient client;

float temp;
float hum;

long previousTime = 0;

void readAndSend() {
   Serial.println("Reading data from sensor...");
   temp = dht.readTemperature(false); // false - teplota v Celsiich, true - ve fahreheitech
   hum = dht.readHumidity();

   // logovani posilanych dat
   Serial.print("Temperature: ");
   Serial.print(temp);
   Serial.print("\tHumidity: ");
   Serial.println(hum);

   client.sendData(temp, hum);
}

void handleDataSent(int httpResult) {
   Serial.print("HttpResult: ");
   Serial.print(httpResult);
   if (httpResult >= 200 && httpResult < 300) {
      Serial.println(" - OK");
      blinker.init({10}, 1);
   } else {
      Serial.println(" - FAILED");
      blinker.init({10,50,10,50,10}, 1);
   }
   blinker.start();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  blinker.stop();

  client.sentCallback(handleDataSent);

  CustomWiFiManager::start(&blinker);

  delay(100);
  dht.begin();

  readAndSend();

  ESP.deepSleep(DEEP_SLEEP_TIME, WAKE_RF_DEFAULT);
}

void loop() {
  // netreba implementovat, vse je v metode setup()
}

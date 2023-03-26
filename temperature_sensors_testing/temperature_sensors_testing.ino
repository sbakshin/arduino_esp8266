#include <DHT.h>

DHT dhtOne(D8, DHT11);

unsigned long timing1 = 0;

void setup() {
  dhtOne.begin();
  Serial.begin(115200);
}

void loop() {
  if (millis() - timing1 > 2000) {
    timing1 = millis();
    float t = dhtOne.readTemperature();
    float h = dhtOne.readHumidity();

    Serial.println(millis()/1000);
    Serial.print("Temprature: ");
    Serial.println(t);
    Serial.print("Humidity: ");
    Serial.println(h);
  }
}
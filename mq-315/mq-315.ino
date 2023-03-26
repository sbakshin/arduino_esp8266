#include "MQ135.h"
#include <DHT.h>

MQ135 gasSensor = MQ135(A0);
DHT dht(D8, DHT11);

unsigned long timing1 = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  if (millis() - timing1 > 10000) {
    timing1 = millis();

    getSensorsData();
  }
}

void getSensorsData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM();

  Serial.println(millis() / 1000);
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("RZero: ");
  Serial.println(rzero);
  Serial.print("PPM: ");
  Serial.println(ppm);
}

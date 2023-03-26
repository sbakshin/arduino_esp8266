#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

DHT dhtOne(15, DHT11);
DHT dhtTwo(13, DHT11);

OneWire oneWire(14);
DallasTemperature sensors(&oneWire);

unsigned long timing1 = 0;

void setup() {
  dhtOne.begin();
  dhtTwo.begin();
  sensors.begin();

  Serial.begin(115200);

  Serial.print("Start");
}

void loop() {
  if (millis() - timing1 > 10000) {
    timing1 = millis();
    float t1 = dhtOne.readTemperature();
    float h1 = dhtOne.readHumidity();
    float t2 = dhtTwo.readTemperature();
    float h2 = dhtTwo.readHumidity();

    sensors.requestTemperatures(); 

    Serial.println(millis()/1000);
    Serial.print("Temprature-1: ");
    Serial.println(t1);
    Serial.print("Temprature-2: ");
    Serial.println(t2);
    Serial.print("Temprature-3: ");
    Serial.println(sensors.getTempCByIndex(0));
    Serial.print("Humidity-1: ");
    Serial.println(h1);
    Serial.print("Humidity-2: ");
    Serial.println(h2);
  }
}
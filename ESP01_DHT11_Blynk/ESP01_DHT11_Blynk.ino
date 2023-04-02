#include <WiFi_ENV.h>
#include <Blynk_ENV.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

BlynkTimer timer;

DHT dhtOne(0, DHT11);


void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  float t1 = dhtOne.readTemperature();
  float h1 = dhtOne.readHumidity();
    
  Blynk.virtualWrite(V10, t1);
  Blynk.virtualWrite(V11, h1);
}

void setup()
{
  dhtOne.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, WiFi_ssid, WiFi_password);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

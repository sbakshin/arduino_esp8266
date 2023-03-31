#include "MQ135.h"
#include <DHT.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <WiFi_ENV.h>

MQ135 gasSensor = MQ135(A0);
DHT dht(D1, DHT11);
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi network
  WiFi.begin(WiFi_ssid, WiFi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM();
  float rzeroc = gasSensor.getCorrectedRZero(t, h);
  float ppmc = gasSensor.getCorrectedPPM(t, h);


  char buffer_t[10];
  char buffer_h[10];
  char buffer_rzero[10];
  char buffer_ppm[10];
  char buffer_rzeroc[10];
  char buffer_ppmc[10];

  dtostrf(t, 5, 2, buffer_t);
  dtostrf(h, 5, 2, buffer_h);
  dtostrf(rzero, 5, 2, buffer_rzero);
  dtostrf(ppm, 5, 2, buffer_ppm);
  dtostrf(rzeroc, 5, 2, buffer_rzeroc);
  dtostrf(ppmc, 5, 2, buffer_ppmc);

  // Serial.print("ppm: ");
  // Serial.println(ppm);

  StreamString temp;
  temp.reserve(500);  // Preallocate a large chunk to avoid memory fragmentation
  temp.printf("\
    <html>\
      <head>\
        <title>MQ-135</title>\
        <style>\
          body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
        </style>\
      </head>\
      <body>\
        <h1>MQ-135 Calibration</h1>\
        <p>Temperature: %s</p>\
        <p>Humidity: %s</p>\
        <p>RZero: %s</p>\
        <p>PPM: %s</p>\
        <p>RZeroCor: %s</p>\
        <p>PPMCor: %s</p>\
      </body>\
    </html>",
              buffer_t, buffer_h, buffer_rzero, buffer_ppm, buffer_rzeroc, buffer_ppmc);
  server.send(200, "text/html", temp.c_str());
}

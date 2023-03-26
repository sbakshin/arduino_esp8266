#include "MQ135.h"

MQ135 gasSensor = MQ135(A0);


void setup() {
  Serial.begin(115200);

}

void loop() {
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM();


  Serial.print("AO: ");
  Serial.println(analogRead (A0));
  Serial.print("Rzero: "); 
  Serial.println(rzero);
  Serial.print("PPM: ");
  Serial.println(ppm );

  delay(5000);
}

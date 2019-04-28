#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write(gpsSerial.read());
}

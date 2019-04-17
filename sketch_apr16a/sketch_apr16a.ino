#include <SoftwareSerial.h>

SoftwareSerial gps(11, 10);

void setup() {
  Serial.begin(9600);

  gps.begin(9600);
  delay(1000);

}

void loop() {
  if(gps.available()){
    Serial.write(gps.read());
  }

}

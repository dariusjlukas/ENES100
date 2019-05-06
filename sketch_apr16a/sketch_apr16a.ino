
/*
 * Library: https://github.com/bolderflight/MPU9250
Basic_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*
 * Updated by Ahmad Shamshiri on July 09, 2018 for Robojax.com
 * in Ajax, Ontario, Canada
 * watch instrucion video for this code: 
For this sketch you need to connect:
VCC to 5V and GND to GND of Arduino
SDA to A4 and SCL to A5

S20A is 3.3V voltage regulator MIC5205-3.3BM5
*/

#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
float accelVals[10];
uint32_t initialTime = 0;
float velocity = 0;
int i = 0;
float jerk = 0;
const float jerkOffset = .15;
double v = 0; //Velocity
long lastTime = 0;
float accelOffset = -0.35;

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  else{
    //Serial.println("Gyro initialization [OK]");
  }
  lastTime = millis();
}

void loop() {
  //read the sensor
  IMU.readSensor();
  
  initialTime = millis();
  i = 0;
  while(i < 10){
    IMU.readSensor();
    accelVals[i] = IMU.getAccelX_mss();
    i++;
  }
  if(i == 10){
    float sum = 0;
    for(int j = 0; j < 10; j++){
      sum = sum + accelVals[j];
    }
    jerk = sum/(millis() - initialTime);
    //Serial.print(millis() - initialTime);
     // Serial.print(" ");
    i = 0;
    sum = 0;
  }
  jerk = jerk - jerkOffset;
  if(i > 10){
    Serial.println("i is greater than max (10)");
  }
  jerk = jerk - IMU.getAccelX_mss();
  if(abs(jerk) > 2){
    Serial.println("Obstacle hit");
  }

  Serial.println(IMU.getMagX_uT());
  
  // display the data
  //Serial.print(jerk - IMU.getAccelX_mss());
  //Serial.print("    ");
  //Serial.println(IMU.getAccelX_mss());
  //Serial.print("AccelX: ");
//  Serial.print(IMU.getAccelX_mss(),6);
//  Serial.print("  ");
//  //Serial.print("AccelY: ");  
//  Serial.print(IMU.getAccelY_mss(),6);
//  Serial.print("  ");
//  //Serial.print("AccelZ: ");  
//  Serial.print(IMU.getAccelZ_mss(),6);
//  Serial.print("  ");
//  
////  Serial.print("GyroX: ");
//  Serial.print(IMU.getGyroX_rads(),6);
//  Serial.print("  ");
////  Serial.print("GyroY: ");  
//  Serial.print(IMU.getGyroY_rads(),6);
//  Serial.print("  ");
////  Serial.print("GyroZ: ");  
//  Serial.print(IMU.getGyroZ_rads(),6);
//  Serial.print("  ");
////
  Serial.print("MagX: ");  
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("  ");  
  Serial.print("MagY: ");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("  ");
  Serial.print("MagZ: ");  
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("  ");
////  
////  Serial.print("Temperature in C: ");
//  Serial.println(IMU.getTemperature_C(),6);
  Serial.println();
////  delay(200);
} 

#include <Arduino.h>
#include <Wire.h>
#include "motor.h"
#include "motor.cpp"
#include "laserRange.h"
#include "laserRange.cpp"
#include <Servo.h>

int leftMotorSpeedPin = 12;
int leftMotorDirPin = 11;
int rightMotorSpeedPin = 10;
int rightMotorDirPin = 9;
long distance = -1;
int sensorServoPos = 0;
int deltaSensorServoPos = 1;
unsigned long startMillis = 0;
int i = 0;
bool backupFlag = false;

MotorController motors(leftMotorDirPin, leftMotorSpeedPin, rightMotorDirPin, rightMotorSpeedPin);  //Create a motor controller object

Servo sensorServo;
LaserRange laserRangefinder(85);  //Create a laser rangefinder object

void setup(){
  laserRangefinder.setup();
  //Wire.begin();
  Serial.begin(9600);
  Serial.println("Starting up...");
  sensorServo.attach(7);

  pinMode(leftMotorSpeedPin, OUTPUT);
  pinMode(leftMotorDirPin, OUTPUT);
  pinMode(rightMotorSpeedPin, OUTPUT);
  pinMode(rightMotorDirPin, OUTPUT);

}

void loop() {

  sweepServo();

  distance = laserRangefinder.getRange();

  
  Serial.println(distance);

  if(distance > 30 && backupFlag == false){
    motors.move(15);
  }
  else{
    backupFlag = true;
  }

  if(backupFlag){
    if(i >= 4){
      i = 0;
    }
    if(millis() - startMillis >= 500){
      i = i + 1;
      startMillis = millis();
    }
    switch (i)
    {
      case 0:
        motors.move(0);
        break;
      case 1:
        motors.move(-20);
        break;
      case 2:
        motors.turnRight(random(15,30));
        break;
      case 3:
        motors.move(0);
        break;
      case 4:
        backupFlag = false;
        break;
      default:
        break;
    }
  }

  distance = 0; //reset the distance variable
}

void sweepServo(){
  if(sensorServoPos <= 0){
    sensorServoPos = 1;
    deltaSensorServoPos = -1 * deltaSensorServoPos;
  }
  if(sensorServoPos >= 180){
    sensorServoPos = 179;
    deltaSensorServoPos = -1 * deltaSensorServoPos;
  }
  sensorServoPos  = sensorServoPos + deltaSensorServoPos;
  //Serial.println(sensorServoPos);
  sensorServo.write(sensorServoPos);
}
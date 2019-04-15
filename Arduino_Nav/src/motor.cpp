#include <Arduino.h>
class MotorController{

    private:
    int leftMotorDirPin;
    int leftMotorSpeedPin;
    int rightMotorDirPin;
    int rightMotorSpeedPin;

    public:
    MotorController(int a, int b, int c, int d){
        leftMotorDirPin = a;
        leftMotorSpeedPin = b;
        rightMotorDirPin = c;
        rightMotorSpeedPin = d;
    }

void move(int speed){
    if(speed > 255){
        Serial.println("Speed value out of range");
    }

    if(speed >= 0){
        digitalWrite(leftMotorDirPin, LOW);
        analogWrite(leftMotorSpeedPin, speed);

        digitalWrite(rightMotorDirPin, HIGH);
        analogWrite(rightMotorSpeedPin, speed);
    }
    else{
        digitalWrite(leftMotorDirPin, HIGH);
        analogWrite(leftMotorSpeedPin, abs(speed));

        digitalWrite(rightMotorDirPin, LOW);
        analogWrite(rightMotorSpeedPin, abs(speed));
    }
}

void turnRight(int speed){
    if(speed > 255){
        Serial.println("Speed value out of range");
    }

    if(speed >= 0){
        digitalWrite(leftMotorDirPin, LOW);
        analogWrite(leftMotorSpeedPin, speed);

        digitalWrite(rightMotorDirPin, LOW);
        analogWrite(rightMotorSpeedPin, speed);
    }

}

void turnLeft(int speed){
    if(speed > 255){
        Serial.println("Speed value out of range");
    }

    if(speed >= 0){
        digitalWrite(leftMotorDirPin, HIGH);
        analogWrite(leftMotorSpeedPin, speed);

        digitalWrite(rightMotorDirPin, HIGH);
        analogWrite(rightMotorSpeedPin, speed);
    }

}

};
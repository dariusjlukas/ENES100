#include "TankSimulation.h"

TankSim::TankSim() {

}

void TankSim::begin(){ 
  Serial.begin(9600);
}

void TankSim::setLeftMotorPWM(int pwm) {
    if (pwm > 255) {
        pwm = 255;
    } else if (pwm < -255) {
        pwm = -255;
    }

    Serial.print("#l");
    Serial.print(pwm);
    Serial.print("*");
    Serial.flush();

}

void TankSim::setRightMotorPWM(int pwm) {
    if (pwm > 255) {
        pwm = 255;
    } else if (pwm < -255) {
      pwm = -255;
    }

    Serial.print("#r");
    Serial.print(pwm);
    Serial.print("*");
    Serial.flush();
  
}

void TankSim::turnOffMotors() {

    Serial.print("#r");
    Serial.print(0);
    Serial.print("*");

    Serial.print("#l");
    Serial.print(0);
    Serial.print("*");

    Serial.flush();
}
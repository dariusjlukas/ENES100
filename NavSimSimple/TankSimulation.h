#ifndef TankSimulation_h
#define TankSimulation_h

#include <Arduino.h>

class TankSim {

public:

    TankSim();
    void begin();

    void turnOffMotors();
    void setRightMotorPWM(int pwm);
    void setLeftMotorPWM(int pwm);

};

#endif
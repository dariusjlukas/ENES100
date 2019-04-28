#include <arduino.h>
#include "Enes100Simulation.h"
#include "../NavSimSimple/Enes100Simulation.h"
#include "../NavSimSimple/TankSimulation.h"
#include "detectContact.h"


constexpr float precision = 0.1;

void simulationInit(){
    
}

void rotateTo(float targetTheta, float motorSpeed){
    Enes100Simulation.updateLocation();
    float delta = 1;
    if(abs(Enes100Simulation.location.theta - targetTheta) > 3.1415926){
        delta = -delta;
    }
    while(abs(Enes100Simulation.location.theta - targetTheta) > 0.1){
        Enes100Simulation.updateLocation();
        TankSimulation.setLeftMotorPWM(delta * motorSpeed);
        TankSimulation.setRightMotorPWM(-delta * motorSpeed);
    }
    TankSimulation.turnOffMotors();
}

void moveToY(float targetY, float closeDistance, float motorSpeed){
    float obstacleDistance = 100;
    while (abs(Enes100Simulation.location.y - targetY) > closeDistance)      //Move until the OSV is lined up with the taget
    {
        //Update the distance to the closest obstacle (including the wall)
        Enes100Simulation.updateLocation();
        obstacleDistance = detectContact(Enes100Simulation.readDistanceSensor(0),
                                         Enes100Simulation.readDistanceSensor(2),
                                         Enes100Simulation.location.x,
                                         Enes100Simulation.location.y);
        if(obstacleDistance < closeDistance){
            TankSimulation.turnOffMotors(); //If there is an obstacle too close, stop ///Update this behavior///
        }
        else{
            TankSimulation.setLeftMotorPWM(motorSpeed);
            TankSimulation.setRightMotorPWM(motorSpeed);
        }

        Enes100Simulation.print(abs(Enes100Simulation.location.y - targetY));
        Enes100Simulation.print("   ");
        Enes100Simulation.println(obstacleDistance);
    }
}
#include <Arduino.h>
#include "Enes100SimulationLocal.h"
#include "TankSimulation.h"
#include "detectContact.h"
#include "movement.h"
#include "Enes100.h"

float precision = 0.05;

void simulationInit()
{
    TankSimulation.begin();

    while (!Enes100Simulation.begin())
    {
        Enes100Simulation.println("Unable to connect to simulation");
    }

    Enes100Simulation.println("Starting Navigation");

    while (!Enes100Simulation.updateLocation())
    {
        Enes100Simulation.println("Unable to update Location");
    }
}

void updateLocation()
{
    Enes100Simulation.updateLocation();
}

float getDestinationY()
{
    while(!Enes100Simulation.updateLocation()){
    }
    return Enes100Simulation.destination.y;
}

float getDestinationX()
{
    Enes100Simulation.updateLocation();
    return Enes100Simulation.destination.x;
}

float getLocationY()
{
    Enes100Simulation.updateLocation();
    return Enes100Simulation.location.y;
}

float getLocationX()
{
    while(!Enes100Simulation.updateLocation()){
    }
    return Enes100Simulation.location.x;
}

void stop()
{
    TankSimulation.turnOffMotors();
}

float closestObstacle()
{
    Enes100Simulation.updateLocation();
    return detectContact(Enes100Simulation.readDistanceSensor(0),
                         Enes100Simulation.readDistanceSensor(2),
                         Enes100Simulation.location.x,
                         Enes100Simulation.location.y);
}

void rotateTo(float targetTheta, float motorSpeed)
{
    Enes100Simulation.updateLocation();
    float delta = 1;
    if (abs(Enes100Simulation.location.theta - targetTheta) >= 3.1415926)
    {
        delta = -delta;
    }
    while (abs(Enes100Simulation.location.theta - targetTheta) > 0.05)
    {
        Enes100Simulation.updateLocation();
        TankSimulation.setLeftMotorPWM(delta * motorSpeed);
        TankSimulation.setRightMotorPWM(-delta * motorSpeed);
        Enes100Simulation.println(Enes100Simulation.location.theta);
    }
    TankSimulation.turnOffMotors();
}

void moveToY(float targetY, float closeDistance, float motorSpeed)
{
    Enes100Simulation.updateLocation();
    float obstacleDistance = 100;
    while (abs(Enes100Simulation.location.y - targetY) > precision) //Move until the OSV is lined up with the taget
    {
        //Update the distance to the closest obstacle (including the wall)
        Enes100Simulation.updateLocation();
        obstacleDistance = detectContact(Enes100Simulation.readDistanceSensor(0),
                                         Enes100Simulation.readDistanceSensor(2),
                                         Enes100Simulation.location.x,
                                         Enes100Simulation.location.y);
        if (obstacleDistance < closeDistance)
        {
            TankSimulation.turnOffMotors(); //If there is an obstacle too close, stop ///Update this behavior///
        }
        else
        {
            TankSimulation.setLeftMotorPWM(motorSpeed);
            TankSimulation.setRightMotorPWM(motorSpeed);
        }

        Enes100Simulation.print(abs(Enes100Simulation.location.y - targetY));
        Enes100Simulation.print("   ");
        Enes100Simulation.println(obstacleDistance);
    }
}

void moveToX(float targetX, float closeDistance, float motorSpeed)
{
    Enes100Simulation.updateLocation();
    float obstacleDistance = 100;
    while (abs(Enes100Simulation.location.x - targetX) > precision) //Move until the OSV is lined up with the taget
    {
        //Update the distance to the closest obstacle (including the wall)
        Enes100Simulation.updateLocation();
        obstacleDistance = detectContact(Enes100Simulation.readDistanceSensor(0),
                                         Enes100Simulation.readDistanceSensor(2),
                                         Enes100Simulation.location.x,
                                         Enes100Simulation.location.y);
        if (obstacleDistance < closeDistance)
        {
            TankSimulation.turnOffMotors(); //If there is an obstacle too close, stop ///Update this behavior///
        }
        else
        {
            TankSimulation.setLeftMotorPWM(motorSpeed);
            TankSimulation.setRightMotorPWM(motorSpeed);
        }

        Enes100Simulation.print(abs(Enes100Simulation.location.x - targetX));
        Enes100Simulation.print("   ");
        Enes100Simulation.println(obstacleDistance);
    }
}

#include "Enes100Simulation.h"
#include "TankSimulation.h"
#include "detectContact.h"

float m_motor_speed = 100;
float obstacleDistance = 100;

//Note: All functions work off of the cordinate system in the simulator, so be sure to convert all distance and cordinate values to this scaling

void setup()
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

void loop()
{

    //turn to face forward
    while (abs(Enes100Simulation.location.theta) > 0.05)
    {

        TankSimulation.setLeftMotorPWM(m_motor_speed);
        TankSimulation.setRightMotorPWM(-m_motor_speed);

        while (!Enes100Simulation.updateLocation())
        {
            Enes100Simulation.println("Unable to update location");
        }
    }

    //Update the distance to the closest obstacle (including the wall)
    obstacleDistance = detectContact(Enes100Simulation.readDistanceSensor(0),
                                     Enes100Simulation.readDistanceSensor(2),
                                     Enes100Simulation.location.x,
                                     Enes100Simulation.location.y);

    //move forward
    TankSimulation.setLeftMotorPWM(255);
    TankSimulation.setRightMotorPWM(255);

    while (obstacleDistance > 0.2)
    {
        //Update the distance to the closest obstacle (including the wall)
        obstacleDistance = detectContact(Enes100Simulation.readDistanceSensor(0),
                                         Enes100Simulation.readDistanceSensor(2),
                                         Enes100Simulation.location.x,
                                         Enes100Simulation.location.y);

        Enes100Simulation.println(obstacleDistance);
    }

    //stop once an obstacle is seen
    TankSimulation.turnOffMotors();
    Enes100Simulation.println("Found Obstacle");

    while (1)
        ;
}
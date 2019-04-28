#include "detectContact.h"
#include "movement.h"
#include "../NavSimSimple/Enes100Simulation.h"
#include "../NavSimSimple/TankSimulation.h"


SimulatorClient Enes100Simulation;  //Define the simulation objects
TankSim TankSimulation;


float m_motor_speed = 100;  //medium motor speed
float obstacleDistance = 100;
float closeDistance = 0.2;

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

    //turn such that the rover is lined up with the target
    Enes100Simulation.updateLocation();
    if(Enes100Simulation.destination.y > Enes100Simulation.location.y){
        rotateTo(3.14159, m_motor_speed);   //Turn to face down
    }
    else{   //Turn to face down
        rotateTo(-3.14159, m_motor_speed);  //Turn to face up
    }

    //Update the OSV location
    Enes100Simulation.updateLocation();
    
    //Move such that the OSV is lines up with the target in the y-direction
    moveToY(Enes100Simulation.destination.y, closeDistance, m_motor_speed);

    //stop once an obstacle is seen
    TankSimulation.turnOffMotors();
    Enes100Simulation.println("Lined up with target");

    while (1)
        ;
}
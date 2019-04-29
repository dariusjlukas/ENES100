#include "detectContact.h"
#include "movement.h"
//#include "Enes100SimulationLocal.h"
//#include "TankSimulation.h"


#define m_motor_speed 100  //medium motor speed
float obstacleDistance = 100;
float closeDistance = 0.2;

//Note: All functions work off of the cordinate system in the simulator, so be sure to convert all distance and cordinate values to this scaling

void setup()
{
   simulationInit();
}

void loop()
{

    //turn such that the rover is lined up with the target
    updateLocation();
    if(getDestinationY() > getLocationX()){
        rotateTo(3.14159, m_motor_speed);   //Turn to face down
    }
    else{   //Turn to face down
        rotateTo(-3.14159, m_motor_speed);  //Turn to face up
    }

    //Update the OSV location
    updateLocation();
    
    //Move such that the OSV is lines up with the target in the y-direction
    moveToY(getDestinationY(), closeDistance, m_motor_speed);

    //stop once an obstacle is seen
    stop();
    Serial.println("Lined up with target");
    Serial.flush();

    while (1)
        ;
}
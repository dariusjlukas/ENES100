#include "detectContact.h"
#include "movement.h"
//#include "Enes100SimulationLocal.h"
//#include "TankSimulation.h"

#define m_motor_speed 100 //medium motor speed
float obstacleDistance = 100;
float closeDistance = 0.15;
constexpr float maxX = 3.8;
constexpr float maxY = 1.85;

//Note: All functions work off of the cordinate system in the simulator, so be sure to convert all distance and cordinate values to this scaling

void setup()
{
    simulationInit();
}

void loop()
{

    //turn such that the rover is lined up with the center of the field
    updateLocation();
    if (getLocationY() < 1)
    {
        rotateTo(3.14159 / 2, m_motor_speed); //Turn to face up
    }
    else
    {                                          //Turn to face down
        rotateTo(-3.14159 / 2, m_motor_speed); //Turn to face down
    }

    //Update the OSV location
    updateLocation();

    //Move such that the OSV is lined up with the center of the field
    moveToY(1, closeDistance, m_motor_speed);

    stop();
    Serial.println("Y lined up with target");
    Serial.flush();

    //Turn to the right
    rotateTo(0, m_motor_speed);

    //Move until an obstacle is spotted, or until the x-coordinate of the rover and the target line up
    while (abs(getLocationX() - getDestinationX()) > 0.05)
    {
        if (closestObstacle() < (closeDistance))
        {
            Serial.println("Avoiding obstacle");
            Serial.flush();
            if(getLocationY() > getDestinationY()){
                rotateTo(-(3.14159/2), m_motor_speed);
                moveToY((getLocationY() - 0.3), closeDistance - 0.05, m_motor_speed);   //Try to avoid the obstacle
            }
            else{
                rotateTo((3.14159/2), m_motor_speed);
                moveToY((getLocationY() + 0.3), closeDistance - 0.05, m_motor_speed);   //Try to avoid the obstacle
            }
            
            rotateTo(0, m_motor_speed);
        }
        else
        {
            Serial.println("Moving toward target");
            Serial.flush();
            moveToX((getLocationX() + 0.1), closeDistance - 0.05, m_motor_speed);
        }
    }
    stop();

    Serial.println("X lined up with target");
    Serial.flush();
    if (getDestinationY() > getLocationY())
    {
        rotateTo(3.14159 / 2, m_motor_speed); //Turn to face up
    }
    else
    {                                          //Turn to face down
        rotateTo(-3.14159 / 2, m_motor_speed); //Turn to face down
    }
    //Move such that the OSV is lined up with the target in the y-direction
    moveToY(getDestinationY(), closeDistance, m_motor_speed);
    stop();
    Serial.println("Target Reached");
    Serial.flush();

    while (1)
        ;
}
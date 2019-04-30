#include <Arduino.h>
#include "detectContact.h"
#include "movementHardware.h"
#include "Enes100Local.h"

int leftMSpeed = 5;
int leftMDir = 4;
int rightMSpeed = 7;
int rightMDir = 6;

float precision = 0.05;

void roverInit(int id)
{
    //while (!Enes100.begin("The T ID", DEBRIS, id, 10, 11))
    //{
    //}
    Enes100.begin("The T ID", DEBRIS, id, 10, 11);
    pinMode(leftMSpeed, OUTPUT); //Set the motor controller pins to output
    pinMode(leftMDir, OUTPUT);
    pinMode(rightMSpeed, OUTPUT);
    pinMode(rightMDir, OUTPUT);
}

void roverInit(int id, int motorAPWM, int motorBPWM, int motorADir, int motorBDir)
{
    while (!Enes100.begin("The T ID", DEBRIS, id, 10, 11))
    {
    }
    leftMSpeed = motorAPWM; //Update the motor pin assignments
    leftMDir = motorADir;
    rightMSpeed = motorBPWM;
    rightMDir = motorBDir;

    pinMode(leftMSpeed, OUTPUT); //Set the motor controller pins to output
    pinMode(leftMDir, OUTPUT);
    pinMode(rightMSpeed, OUTPUT);
    pinMode(rightMDir, OUTPUT);
}

void updateLocation()
{
    Enes100.updateLocation();
}

float getDestinationY()
{

    return Enes100.destination.y;
}

float getDestinationX()
{
    return Enes100.destination.x;
}

float getLocationY()
{
    while (!Enes100.updateLocation())
    {
    }
    return Enes100.location.y;
}

float getLocationX()
{
    while (!Enes100.updateLocation())
    {
    }
    return Enes100.location.x;
}

void stop()
{
    digitalWrite(leftMDir, HIGH);   //Default the direction pins to high
    digitalWrite(rightMDir, HIGH);
    analogWrite(leftMSpeed, 0); //Stop the motors
    analogWrite(rightMSpeed, 0);
}

float closestObstacle()
{
    updateLocation(); 
    //Read the ultrasonic sensors
    long duration; //Duration and distance values from the ultrasonic sensor
    double distance;
    double distArray[10];
    int distArrayCount = 0;
    double averageDistance1 = -1;
    double averageDistance2 = -1;
    //Clear the trigger pin

    //Read the first ultrasonic sensor
    while(distArrayCount < 10){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); ////!!!Fix this with scheduling!!!///
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); ////!!!Fix this with scheduling!!!///
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); //Read the duration of the pulse on the echo pin

    distance = duration * 0.034 / 2;

    if (distance > 50)
    { //If the distance is greater than 50, cap it to 55
        distance = 55;
    }

    distArray[distArrayCount] = distance;

    if (distArrayCount == 9)
    {
        for (int i = 0; i < 10; i++)
        {
            averageDistance1 = averageDistance1 + distArray[i];
        }
        averageDistance1 = averageDistance1 / 10;
        distArrayCount++;
    }
    else
    {
        distArrayCount++;
    }
    }

    distArrayCount = 0;
    //Read the second ultrasonic sensor
    while(distArrayCount < 10){
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2); ////!!!Fix this with scheduling!!!///
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10); ////!!!Fix this with scheduling!!!///
    digitalWrite(trigPin2, LOW);

    duration = pulseIn(echoPin2, HIGH); //Read the duration of the pulse on the echo pin

    distance = duration * 0.034 / 2;

    if (distance > 50)
    { //If the distance is greater than 50, cap it to 55
        distance = 55;
    }

    distArray[distArrayCount] = distance;

    if (distArrayCount == 9)
    {
        for (int i = 0; i < 10; i++)
        {
            averageDistance2 = averageDistance2+ distArray[i];
        }
        averageDistance2 = averageDistance2 / 10;
        distArrayCount++;
    }
    else
    {
        distArrayCount++;
    }
    }

    //Convert from distance in cm to distance in field units
    averageDistance1 = averageDistance1 * 0.01; //The field units are in meters and the ultrasonic sensors work in centimeters
    averageDistance2 = averageDistance2 * 0.01;

    return detectContact(averageDistance1,
                         averageDistance2,
                         Enes100.location.x,
                         Enes100.location.y); //This test uses a single ultrasonic sensor, so the other distance is set to a large value

    //Testing setup
    // return detectContact(
    //     averageDistance1,
    //     averageDistance2,
    //     1,
    //     1
    // );
}

void rotateTo(float targetTheta, float motorSpeed)
{
    Enes100.updateLocation();
    float delta = 1;
    if (abs(Enes100.location.theta - targetTheta) >= 3.1415926)
    {
        delta = -delta;
    }
    while (abs(Enes100.location.theta - targetTheta) > 0.05)
    {
        Enes100.updateLocation();
        if(delta >= 0){
            digitalWrite(leftMDir, HIGH);
            digitalWrite(rightMDir, LOW);
            analogWrite(leftMSpeed, motorSpeed);
            analogWrite(rightMSpeed, motorSpeed);
        }
        else{
            digitalWrite(leftMDir, LOW);
            digitalWrite(rightMDir, HIGH);
            analogWrite(leftMSpeed, motorSpeed);
            analogWrite(rightMSpeed, motorSpeed);
        }
        Serial.println(Enes100.location.theta);
    }
    stop();
}

void moveToY(float targetY, float closeDistance, float motorSpeed)
{
    Enes100.updateLocation();
    float obstacleDistance = 100;
    while (abs(Enes100.location.y - targetY) > precision) //Move until the OSV is lined up with the target
    {
        //Update the distance to the closest obstacle (including the wall)
        Enes100.updateLocation();
        obstacleDistance = closestObstacle();
        if (obstacleDistance < closeDistance)
        {
            stop(); //If there is an obstacle too close, stop ///Update this behavior///
        }
        else
        {
            digitalWrite(leftMDir, HIGH);
            digitalWrite(rightMDir, HIGH);
            analogWrite(leftMSpeed, motorSpeed);
            analogWrite(rightMSpeed, motorSpeed);
        }

        Serial.print(abs(Enes100.location.y - targetY));
        Serial.print("   ");
        Serial.println(obstacleDistance);
    }
}

void moveToX(float targetX, float closeDistance, float motorSpeed)
{
    Enes100.updateLocation();
    float obstacleDistance = 100;
    while (abs(Enes100.location.x - targetX) > precision) //Move until the OSV is lined up with the taget
    {
        //Update the distance to the closest obstacle (including the wall)
        Enes100.updateLocation();
        obstacleDistance = closestObstacle();
        if (obstacleDistance < closeDistance)
        {
            stop(); //If there is an obstacle too close, stop ///Update this behavior///
        }
        else
        {
            digitalWrite(leftMDir, HIGH);
            digitalWrite(rightMDir, HIGH);
            analogWrite(leftMSpeed, motorSpeed);
            analogWrite(rightMSpeed, motorSpeed);
        }

        Serial.print(abs(Enes100.location.x - targetX));
        Serial.print("   ");
        Serial.println(obstacleDistance);
    }
}

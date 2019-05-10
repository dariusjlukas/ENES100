#include <Arduino.h>
#include "detectContact.h"
#include "movementHardware.h"
#include <Enes100.h>

int leftMSpeed = 5;
int leftMDir = 4;
int rightMSpeed = 7;
int rightMDir = 6;

float LMotorSpeedOffset = 1.0; //Speed offsets (trim) Bigger numbers are sower
float RMotorSpeedOffset = 1.0;

float precision = 0.2;

void roverInit(int id)
{
    while (!Enes100.begin("The T ID", DEBRIS, id, 10, 11))
    {
    }
    //Enes100.begin("The T ID", DEBRIS, id, 10, 11);
    //Serial.println("Set up complete");
    pinMode(leftMSpeed, OUTPUT); //Set the motor controller pins to output
    pinMode(leftMDir, OUTPUT);
    pinMode(rightMSpeed, OUTPUT);
    pinMode(rightMDir, OUTPUT);
    pinMode(12, INPUT);
    //while(digitalRead(12) == LOW){  //Wait for the jumper on pin 12 to go high
    //    Enes100.println("Waiting for jumper connection");
    //}
}

void printDestination()
{
    Enes100.updateLocation();
    Enes100.print(Enes100.destination.x);
    Enes100.print("     ");
    Enes100.println(Enes100.destination.y);
}

void printLocation()
{
    Enes100.updateLocation();
    Enes100.print(Enes100.location.x);
    Enes100.print("     ");
    Enes100.println(Enes100.location.y);
}

void printLocationTheta()
{
    Enes100.updateLocation();
    Enes100.println(Enes100.location.theta);
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
    return Enes100.location.y;
}

float getLocationX()
{
    return Enes100.location.x;
}

void setX(float x){ //For testing only, manually set the x-coordinate of the rover
    Enes100.location.x = x;
}

void setY(float y){ //For testing only, manually set the y-coordinate of the rover
    Enes100.location.y = y;
}

void stop()
{
    digitalWrite(leftMDir, LOW);   //Default the direction pins to high
    digitalWrite(rightMDir, LOW);
    digitalWrite(leftMSpeed, LOW); //Stop the motors
    digitalWrite(rightMSpeed, LOW);
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

float hABS(float input){
    if(input >=0){
        return input;
    }
    else{
        return -1.0 * input;
    }
}

void rotateTo(float targetTheta, float motorSpeed)
{
    Enes100.updateLocation();
    float delta = 1.0;
    if (Enes100.location.theta - targetTheta >= 3.1415926)
    {
        delta = -1.0;
    }
    while (hABS((float)Enes100.location.theta - (float)targetTheta) > 0.10)
    {
        Enes100.updateLocation();
        Enes100.print("theta:  ");
        Enes100.println(Enes100.location.theta);
        if(delta >= 0){
            analogWrite(leftMDir, motorSpeed * LMotorSpeedOffset);
            digitalWrite(rightMDir, LOW);
            digitalWrite(leftMSpeed, LOW);
            analogWrite(rightMSpeed, motorSpeed * RMotorSpeedOffset);
            Enes100.println(hABS((float)Enes100.location.theta - (float)targetTheta));
        }
         else{
             digitalWrite(leftMDir, LOW);
             analogWrite(rightMDir, motorSpeed * RMotorSpeedOffset);
             analogWrite(leftMSpeed, motorSpeed * LMotorSpeedOffset);
             digitalWrite(rightMSpeed, LOW);
             Enes100.println(hABS((float)Enes100.location.theta - (float)targetTheta));
        }
    }
    stop();
    Enes100.println("Rotation Complete");

}

void moveToY(float targetY, float closeDistance, float motorSpeed)
{
    Enes100.updateLocation();
    float obstacleDistance = 100;
    while (hABS(Enes100.location.y - targetY) > precision) //Move until the OSV is lined up with the target
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
            analogWrite(leftMDir, motorSpeed * LMotorSpeedOffset);
            analogWrite(rightMDir, motorSpeed * RMotorSpeedOffset);
            digitalWrite(leftMSpeed, LOW);
            digitalWrite(rightMSpeed, LOW);
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
    while (targetX > Enes100.location.x) //Move until the OSV is lined up with the target (ONLY GOES RIGHT)
    {
        //Update the distance to the closest obstacle (including the wall)
        Enes100.updateLocation();
        obstacleDistance = closestObstacle();
        if (obstacleDistance < closeDistance)
        {
            stop(); //If there is an obstacle too close, stop ///Update this behavior///
            digitalWrite(22, HIGH);
            Enes100.println("Obstacle detected");
        }
        else
        {
            digitalWrite(22, LOW);
            analogWrite(leftMDir, motorSpeed * LMotorSpeedOffset);
            analogWrite(rightMDir, motorSpeed * RMotorSpeedOffset);
            digitalWrite(leftMSpeed, LOW);
            digitalWrite(rightMSpeed, LOW);
        }

        Enes100.print(hABS(Enes100.location.x - targetX));
        Enes100.print("   ");
        Enes100.println(obstacleDistance);
    }
}

void move(float closeDistance, float motorSpeed){
    //digitalWrite(leftMDir, LOW);
    //digitalWrite(rightMDir, LOW);
    digitalWrite(leftMDir, LOW);
            analogWrite(rightMDir, motorSpeed * RMotorSpeedOffset);
            analogWrite(leftMSpeed, motorSpeed * LMotorSpeedOffset);
            digitalWrite(rightMSpeed, LOW);
}

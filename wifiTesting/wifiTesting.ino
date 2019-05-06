#include <Enes100.h>

#define m_motor_speed 100 //medium motor speed
#define ID_NUMBER 11 //Set the ID number of the QR marker
#define trigPin 8   //Left Ultrasonic trigger and echo pins
#define echoPin 9

#define trigPin2 3  //Right ultrasonic trigger and echo pins
#define echoPin2 2

float obstacleDistance = 100;
float closeDistance = .15; //Distance where the OSV reacts, in meters
constexpr float maxX = 3.8;
constexpr float maxY = 1.85;

int leftMSpeed = 5;
int leftMDir = 4;
int rightMSpeed = 7;
int rightMDir = 6;

float precision = 0.05;

constexpr auto detectDistance = 1.0;

float detectContact(float sensorVal1, float sensorVal2, float x, float y){
    float xFromWall;
    float yFromWall;

    if(x >= (maxX/2)){
        xFromWall = abs(x - maxX);    //If the rover is on the right side of the field, set the distance from the wall to be 
    }
    else{
        xFromWall = x;    //If the rover is on the right side of the field, set the distance from the wall to be
    }

    if(y >= (maxY/2)){
        yFromWall = abs(y - maxY);
     }
     else{
         yFromWall = y;
     }

    if(sensorVal1 < detectDistance || sensorVal2 < detectDistance || xFromWall < detectDistance || yFromWall < detectDistance){
        //Store the distance values in an array before sorting, assigning the inputs values:
        // 1 : sensorVal1
        // 2 : sensorVal2
        // 3 : xFromWall
        // 4 : yFromWall
        float min1 = min(sensorVal1, sensorVal2);
        float min2 = min(xFromWall, yFromWall);
        return min(min1, min2);

       
        
    }
    else {
        return 100; //Return a large value if the closest obstacle is far away
    }
}

void roverInit(int id)
{
    //while (!Enes100.begin("The T ID", DEBRIS, id, 10, 11))
    //{
    //}
    Enes100.begin("The T ID", DEBRIS, id, 10, 11);
    Serial.println("Set up complete");
    pinMode(leftMSpeed, OUTPUT); //Set the motor controller pins to output
    pinMode(leftMDir, OUTPUT);
    pinMode(rightMSpeed, OUTPUT);
    pinMode(rightMDir, OUTPUT);
    pinMode(12, INPUT);
    while(digitalRead(12) == LOW){  //Wait for the jumper on pin 12 to go high
        Enes100.println("Waiting for jumper connection");
    }
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
    //while (!Enes100.updateLocation())
    //{
    //}
    Enes100.updateLocation();
    return Enes100.location.y;
}

float getLocationX()
{
    //while (!Enes100.updateLocation())
    //{
    //}
    Enes100.updateLocation();
    return Enes100.location.x;
}

void stop()
{
    digitalWrite(leftMDir, HIGH);   //Default the direction pins to high
    digitalWrite(rightMDir, LOW);
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
            digitalWrite(rightMDir, LOW);
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
            digitalWrite(rightMDir, LOW);
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
            digitalWrite(rightMDir, LOW);
            analogWrite(leftMSpeed, motorSpeed);
            analogWrite(rightMSpeed, motorSpeed);
        }

        Serial.print(abs(Enes100.location.x - targetX));
        Serial.print("   ");
        Serial.println(obstacleDistance);
    }
}


//Note: All functions work off of the cordinate system in the simulator, so be sure to convert all distance and cordinate values to this scaling

void setup()
{
    //Serial.begin(9600);
    //Enes100.begin("The T Id", DEBRIS, 6, 10, 11);   //Check the movementHardware file for the TX and RX pins for the radio
    roverInit(6);
    pinMode(trigPin, OUTPUT);   //Set up the pins for the ultrasonic rangefinder
    pinMode(echoPin, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    Enes100.print(getDestinationX());
    Enes100.print("  ");
    Enes100.println(getDestinationY());
}



void loop()
{

  Enes100.updateLocation();
  Enes100.println(closestObstacle());
//     //turn such that the rover is lined up with the center of the field
//     if (getLocationY() < 1)
//     {
//         rotateTo(3.14159 / 2, m_motor_speed); //Turn to face up
//     }
//     else
//     {                                          //Turn to face down
//         rotateTo(-3.14159 / 2, m_motor_speed); //Turn to face down
//     }
//
//     //Update the OSV location
//     updateLocation();
//
//     //Move such that the OSV is lined up with the center of the field
//     moveToY(1, closeDistance, m_motor_speed);
//
//     stop();
//     Enes100.println("Y lined up with target");
//
//     //Turn to the right
//     rotateTo(0, m_motor_speed);
//
//     //Move until an obstacle is spotted, or until the x-coordinate of the rover and the target line up
//     while (abs(getLocationX() - getDestinationX()) > 0.05)
//     {
//         if (closestObstacle() < (closeDistance))
//         {
//             Enes100.println("Avoiding obstacle");
//             
//             if(getLocationY() > getDestinationY()){
//                 rotateTo(-(3.14159/2), m_motor_speed);
//                 moveToY((getLocationY() - 0.3), closeDistance - 0.05, m_motor_speed);   //Try to avoid the obstacle
//             }
//             else{
//                 rotateTo((3.14159/2), m_motor_speed);
//                 moveToY((getLocationY() + 0.3), closeDistance - 0.05, m_motor_speed);   //Try to avoid the obstacle
//             }
//            
//             rotateTo(0, m_motor_speed);
//         }
//         else
//         {
//             Enes100.println("Moving toward target");
//             
//             moveToX((getLocationX() + 0.1), closeDistance - 0.05, m_motor_speed);
//         }
//     }
//     stop();
//
//     Enes100.println("X lined up with target");
//     
//     if (getDestinationY() > getLocationY())
//     {
//         rotateTo(3.14159 / 2, m_motor_speed); //Turn to face up
//     }
//     else
//     {                                          //Turn to face down
//         rotateTo(-3.14159 / 2, m_motor_speed); //Turn to face down
//     }
//     //Move such that the OSV is lined up with the target in the y-direction
//     moveToY(getDestinationY(), closeDistance, m_motor_speed);
//     stop();
//     Enes100.println("Target Reached");
//     while (1)
//         ;
}

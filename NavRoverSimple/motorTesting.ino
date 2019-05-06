// #include <Arduino.h>
// #include "detectContact.h"
// #include "movementHardware.h"

// #define m_motor_speed 100 //medium motor speed
// #define f_motor_speed 200 //fast motor speed
// #define ID_NUMBER 6 //Set the ID number of the QR marker

// float obstacleDistance = 100;
// float closeDistance = .15; //Distance where the OSV reacts, in meters
// constexpr float maxX = 3.8;
// constexpr float maxY = 1.85;

// //Temporary, for testing purposes
// long duration;  //Duration and distance values from the ultrasonic sensor
// int distance;
// int distArray [10];
// int distArrayCount = 0;
// float averageDistance = -1;
// //////////////////////////////////////////

// //Note: All functions work off of the cordinate system in the simulator, so be sure to convert all distance and cordinate values to this scaling

// void setup()
// {
//     Serial.begin(9600);
//     pinMode(trigPin, OUTPUT);   //Set up the pins for the ultrasonic rangefinder
//     pinMode(echoPin, INPUT);
//     pinMode(trigPin2, OUTPUT);
//     pinMode(echoPin2, INPUT);
// }

// void loop()
// {
//   setX(0);
//   setY(0);
//   Serial.println(getLocationX());
//   move(100, f_motor_speed);
//   //moveToX(2, 100, m_motor_speed);
  
// }
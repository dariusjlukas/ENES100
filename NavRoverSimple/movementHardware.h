#ifndef MOVEMENT_HARDWARE
#define MOVEMENT_HARDWARE

void rotateTo(float targetTheta, float movementSpeed);

void moveToY(float targetY, float closeDistance, float motorSpeed);

void moveToX(float targetY, float closeDistance, float motorSpeed);

void roverInit(int id);

void roverInit(int id, int motorAPWM, int motorBPWM, int motorADir, int motorBDir);

void updateLocation();

float getDestinationY();

float getDestinationX();

float getLocationY();

float getLocationX();

void stop();

float closestObstacle();

void setX(float x);

void setY(float y);

void move(float closeDistance, float motorSpeed);

void printDestination();

void printLocation();

void printLocationTheta();

void printAvoid();

float hABS(float input);

//void simPrint(String s);

//void simPrintln(String s);

#define trigPin 8   //Left Ultrasonic trigger and echo pins
#define echoPin 9

#define trigPin2 3  //Right ultrasonic trigger and echo pins
#define echoPin2 2

#endif
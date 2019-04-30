#ifndef MOVEMENT_HARDWARE
#define MOVEMENT_HARDWARE

void rotateTo(float targetTheta, float movementSpeed);

void moveToY(float targetY, float closeDistance, float motorSpeed);

void moveToX(float targetY, float closeDistance, float motorSpeed);

void simulationInit();

void updateLocation();

float getDestinationY();

float getDestinationX();

float getLocationY();

float getLocationX();

void stop();

float closestObstacle();

//void simPrint(String s);

//void simPrintln(String s);


#endif
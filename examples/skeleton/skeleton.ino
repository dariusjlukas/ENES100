#include "Enes100Simulation.h"
#include "TankSimulation.h"

/*
 * Note: This sketch contains function defintions that may be useful for writing your navigation code. 
 * You are responsible for writing the code to complete the functions and testing it out on the simulator. 
 * If you're looking for an example of using the simulator libraries, go to File->Examples->navigation_example
 */

void setup() {
  TankSimulation.begin();
  Enes100Simulation.begin();

  Enes100Simulation.println("Starting Navigation");

  while (!Enes100Simulation.updateLocation()) {
    Enes100Simulation.println("Unable to update Location");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

//This function computes he distance from the OSV to the coordinate passed in
float distanceTo(float x, float y) {
  //parameter: float x - the x value of the coordinate
  //parameter: float y - the y value of the coordinate
  //return value: this function should return a float representing how far the OSV is from the coordinate (x,y)
  //Note: after the OSV's location is updated, its location will be stored in the fields enes.location.x and enes.location.y
  //Hint: The Arduino Math functions will be helpful here
  
}

// This function will move the tank at the given pwm for the given number of seconds.
void goForSeconds(float seconds, int pwm) {
  // parameter: float seconds - The amount of time the tank is expected to travel.
  // paramter: int pwm - The pwm of the motors, ranging from -255 to 255
  
}

// This function will turn the tank to a given angle.
void turnToAngle(float angle) {
  //parameter: float angle - This is the angle you want the OSV to turn to, ranging from -PI to PI
  //Hint: Be careful comparing floating point values
  //Challenge: Try to make the OSV turn as efficiently as possibly, ie. it turns right or left depending on which way is faster
  
}

// This function will turn the OSV 90 degrees left
void turn90DegreesLeft() {
  //This function should turn the OSV 90 degrees left
  //Hint: Can you use the function turnToAngle() to make writing this function easier?
}

// This function will turn the OSV 90 degrees right
void turn90DegreesRight() {
  //This function should turn the OSV 90 degrees right
  //Hint: Can you use the function turnToAngle() to make writing this function easier?
}

//This function will move to OSV to a specific coordinate
void navigateTo(float x, float y) {
  //parameter: float x - the x value of the coordinate
  //parameter: float y - the y value of the coordinate
  //Hint: Can you use the function turnToAngle() to make writing this function easier?
}

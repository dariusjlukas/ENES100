#include "Enes100Simulation.h"
#include "TankSimulation.h"

void setup() {
  TankSimulation.begin();
  while(!Enes100Simulation.begin()) {
    Enes100Simulation.println("Unable to connect to simulation");
  }

  Enes100Simulation.println("Starting Navigation");

  while (!Enes100Simulation.updateLocation()) {
    Enes100Simulation.println("Unable to update Location");
  }

}

void loop() {

  //turn to face forward
  while (abs(Enes100Simulation.location.theta) > 0.05) {

    TankSimulation.setLeftMotorPWM(255);
    TankSimulation.setRightMotorPWM(-255);

    while (!Enes100Simulation.updateLocation()) {
      Enes100Simulation.println("Unable to update location");
    }
    
  }

  //move forward
  TankSimulation.setLeftMotorPWM(255);
  TankSimulation.setRightMotorPWM(255);

  while (Enes100Simulation.readDistanceSensor(1) > 0.2) {
    Enes100Simulation.println("No obstacle seen within 0.2 meters");
  }

  //stop once an obstacle is seen
  TankSimulation.turnOffMotors();
  Enes100Simulation.println("Found Obstacle");

  while(1);
  
}

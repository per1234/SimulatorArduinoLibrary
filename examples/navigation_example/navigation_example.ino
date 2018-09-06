#include "Enes100Simulation.h"
#include "DFRTankSimulation.h"

#define abs(x) ((x)>0?(x):-(x))

Enes100Simulation enes;
DFRTankSimulation tank;

void setup() {

  tank.init();

  enes.println("Starting Navigation");

  while (!enes.retrieveDestination());

  while (!enes.updateLocation());

}

void loop() {

  //turn to face forward
  while (abs(enes.location.theta) > 0.05) {

    tank.setLeftMotorPWM(255);
    tank.setRightMotorPWM(-255);

    while (!enes.updateLocation());
    
  }

  //move forward
  tank.setLeftMotorPWM(255);
  tank.setRightMotorPWM(255);

  while (enes.readDistanceSensor(1) > 0.2) ;

  //stop once an obstacle is seen
  tank.turnOffMotors();
  enes.println("Found Obstacle");

  while(1);

}
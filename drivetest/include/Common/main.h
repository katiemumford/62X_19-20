#include "vex.h"
#include <cmath>

//Define motor ports, change as necessary for wiring
#define LEFT1PORT vex::PORT1
#define LEFT2PORT vex::PORT10

using namespace vex;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition = vex::competition();

vex::motor right1(LEFT1PORT, true);
vex::motor right2(LEFT2PORT, true);


//Standard voltage drive, can scale as needed with the first multiplier
void arm() {
  right1.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  right2.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
}
//Moves the lift, make sure limits are set in correct positions
//Can later be added to macros 

//Moves the 4-bar, make sure states are set in correct positions
//Can later be added to macros 
//As of now unused, but can be added for autonomous control
void wait(int msec) { vex::task::sleep(msec); }

//This is just an initialization function to clean up the main function
//It shouldn't need to be called more than once at the start of the program
void setupMotors(){
  right1.setStopping(vex::brakeType::coast);
  right2.setStopping(vex::brakeType::coast);
  right1.resetRotation();
  right2.resetRotation();
}
//Main control loop
void defaultUserControl() {
  setupMotors();
  while (1) {    
    arm();
    vex::task::sleep(10);
  }
}

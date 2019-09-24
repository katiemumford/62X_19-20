#include "vex.h"
#include "config.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

int minPct = 5; //minimum controller value (%) for drive, accounts for stick drift
bool intaking = false;  //whether the intake has been toggled
int intakeWait = 0; //time since last toggle

int maxPotVal = 1288;
int restPotVal = 2780;


//////////BASIC_FUNCTIONS//////////
#pragma region

void drive(double l,  double r) { //percent drive
  if (l < minPct && l > -minPct) { l = 0; }
  if (r < minPct && r > -minPct) { r = 0; } //accounts for stick drift

  l1.spin(vex::directionType::fwd, l, vex::percentUnits::pct);
  l2.spin(vex::directionType::fwd, l, vex::percentUnits::pct);
  r1.spin(vex::directionType::fwd, r, vex::percentUnits::pct);
  r2.spin(vex::directionType::fwd, r, vex::percentUnits::pct);
}

void vdrive(double l, double r) { //voltage drive
  if (l < minPct && l > -minPct) { l = 0; }
  if (r < minPct && r > -minPct) { r = 0; } //accounts for stick drift
  l *= 12.0/100;
  r *= 12.0/100; //converts to volts

  l1.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  l2.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  r1.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
  r2.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
}

void spinIntake(int pct) {
  if (pct != 0) {
    rin.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
    lin.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    rin.stop(vex::brakeType::brake);
    lin.stop(vex::brakeType::brake);
  }
}

void moveArm(int pct) {
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

void moveTray(int pct) {
  if (pct!= 0) {
    tray.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    tray.stop(vex::brakeType::brake);
  } 
}
#pragma endregion


//////////DRIVER_FUNCTIONS//////////
#pragma region

/**
Sept 23, 2019
Katie wants to change the program 
**/ 

void intakeControl() {

//if R1 is pressed, intake intakes at 100 until unpressed
//if R2 pressed, intake outakes at -100 until unpressed
//if R1 and (shiftKey) L2 pressed, intake intakes at 50 until unpressed
//if R2 and (shiftKey) L2 pressed, intake outakes at -50 until unpressed
if (Controller.ButtonR1.pressing()){
  spinIntake(100);
}
if(Controller.ButtonR2.pressing()){
  spinIntake(-100);
}
if (Controller.ButtonR1.pressing() && Controller.ButtonL2.pressing()){
  spinIntake(50);
}
if (Controller.ButtonR2.pressing() && Controller.ButtonL2.pressing()){
  spinIntake(-50);
}
else{
  spinIntake(0);
}
}
  
  /** dean code
  //if R1 is pressed 200ms since last press, toggle intake on/off
  if (Controller.ButtonR1.pressing() && vex::timer::system() > intakeWait + 200) {
    intaking = !intaking;
    intakeWait = vex::timer::system();
  } 
  if (Controller.ButtonR2.pressing()) { //hold R2 to rev intake
    spinIntake(-100);
    intaking = false;
  } else if (intaking || Controller.ButtonB.pressing()) { //hold B to intake (optional)
    spinIntake(100);
  } else {
    spinIntake(0);
  }
  **/


/**
default you press R1 once and tray goes to stacked position (tuned)
press the same button again and returns to intake position

hold shift key and press R1 and R2(shift key) to get intake arm up to tower height
hold shift key and press R1 again to get intake back down 
**/

void armControl() {

 //if L2 and L1 are pressed 200ms since last press, toggle arm on/off
  if (Controller.ButtonL1.pressing() && Controller.ButtonL2.pressing() && vex::timer::system() > armWait + 200) {
    armMoving = true;
    armWait = vex::timer::system();
  } 
  if (Controller.ButtonL1.pressing() && Controller.ButtonL2 && armMoving ) { //if holding both buttons for the first time
    moveArm(100);  //move arm up to tower height and power 
    armMoving = false;
  } else if (Controller.ButtonL1.pressing() && Controller.ButtonL2 && !armMoving ) {
    moveArm(-100); 
    //figure out exact amount to go back down
    //moveArm needs macro to tilt tray a little bit
  } else {
    moveArm(0);
  }

  /** dean code
  if (Controller.ButtonL1.pressing()) { //hold L1 to move intake arm up
    moveArm(100);
  } else if (Controller.ButtonL2.pressing()) {  //hold L2 to move intake arm down
    moveArm(-70); 
  } else {
    moveArm(0);
  } **/
}

void trayControl() {

//if L1 is pressed 200ms since last press, toggle tilt on/off for forwards then backwards
  if (Controller.ButtonL1.pressing() && vex::timer::system() > tiltWait + 200) {
    tiltingForward = true;    //don't totally know what this does but dean had it?
    tiltWait = vex::timer::system();
  } 
  if (Controller.ButtonR1.pressing() && titltingForward) { //if toggle already pressed and titling forward,
    moveTray(100); //FIGURE OUT PROPER TILt TO GO FORWARD
    tiltingForward = false; 
  } else if (Controller.ButtonL1.pressing() && !tiltingForward) { //hold B to intake (optional)
    moveTray(-100); //FIGURE OUT PROPER TILT TO GO BACK
  } else {
    moveTray(0);
  }

  //manual control buttons 
  if (Controller.ButtonX.pressing()) {  //hold X to move tray up
    moveTray(80);
  } else if (Controller.ButtonA.pressing()) {  //hold A to move tray down
    moveTray(-80);
  } else {
    moveTray(0);
  }
}
#pragma endregion



//////////AUTON_FUNCTIONS//////////
#pragma region

//ONE SQUARE = 1.79 rev
//RIGHT TURN ~ 1.0rev

void wait(int millis) {
  vex::task::sleep(millis);
}

//drive for a given distance, uses built-in encoder function
//program will wait for the drive to finish if wait == true
void basicEncoderDrive(double pct, double rev, bool wait) {
  l1.startRotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  l2.startRotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  r1.startRotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  if (wait) {
    r2.rotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  } else {
    r2.startRotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  }
}

//turn in place for a given distance per wheel, uses built-in encoder function
//program will wait for the turn to finish if wait == true
void basicEncoderTurn(double pct, double rev, bool wait) {
  l1.startRotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  l2.startRotateFor(rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  r1.startRotateFor(-rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  if (wait) {
    r2.rotateFor(-rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  } else {
    r2.startRotateFor(-rev, vex::rotationUnits::rev, pct, vex::velocityUnits::pct);
  }
}

//drive for a given time (in milliseconds)
void timedDrive(double pct, int millis) {
  drive(pct, pct);
  wait(millis);
  drive(0,0);
}
#pragma endregion


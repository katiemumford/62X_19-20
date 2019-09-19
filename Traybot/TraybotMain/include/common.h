#include "vex.h"
#include "config.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

int minPct = 5;
bool intaking = false;
int intakeWait = 0;

/////BASIC_FUNCTIONS/////
#pragma region

void drive(double l,  double r) { //percent drive
  if (l < minPct && l > -minPct) { l = 0; }
  if (r < minPct && r > -minPct) { r = 0; }

  l1.spin(vex::directionType::fwd, l, vex::percentUnits::pct);
  l2.spin(vex::directionType::fwd, l, vex::percentUnits::pct);
  r1.spin(vex::directionType::fwd, r, vex::percentUnits::pct);
  r2.spin(vex::directionType::fwd, r, vex::percentUnits::pct);
}

void vdrive(double l, double r) { //voltage drive
  l *= 12.0/100;
  r *= 12.0/100;

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
    rin.stop(vex::brakeType::hold);
    lin.stop(vex::brakeType::hold);
  }
}

void moveArm(int pct) {
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::hold);
  }
}

void moveTray(int pct) {
  if (pct!= 0) {
    tray.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    tray.stop(vex::brakeType::hold);
  } 
}
#pragma endregion


/////DRIVER_FUNCTIONS/////
#pragma region

void intakeControl() {
  if (Controller.ButtonR1.pressing() && vex::timer::system() > intakeWait + 200) {
    intaking = !intaking;
    intakeWait = vex::timer::system();
  } 
  if (Controller.ButtonR2.pressing()) {
    spinIntake(-100);
    intaking = false;
  } else if (intaking) {
    spinIntake(100);
  } else {
    spinIntake(0);
  }
}

void armControl() {
  if (Controller.ButtonL1.pressing()) {
    moveArm(100);
  } else if (Controller.ButtonL2.pressing()) {
    moveArm(-100);
  } else {
    moveArm(0);
  }
}

void trayControl() {
  if (Controller.ButtonX.pressing()) {
    moveTray(100);
  } else if (Controller.ButtonA.pressing()) {
    moveTray(-100);
  } else {
    moveTray(0);
  }
}
#pragma endregion


/////AUTON_FUNCTIONS/////
#pragma region

void basicEncoderDrive(double pct, int ticks, bool wait) {
  l1.startRotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  l2.startRotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  r1.startRotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  if (wait) {
    r2.rotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  } else {
    r2.startRotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  }
}

void basicEncoderTurn(double pct, int ticks, bool wait) {
  l1.startRotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  l2.startRotateFor(ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  r1.startRotateFor(-ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  if (wait) {
    r2.rotateFor(-ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  } else {
    r2.startRotateFor(-ticks, vex::rotationUnits::raw, pct, vex::velocityUnits::pct);
  }
}

void timedDrive(double pct, int millis) {
  l1.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  l2.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  r1.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  r2.rotateFor(millis, vex::timeUnits::msec, pct, vex::velocityUnits::pct);
}
#pragma endregion


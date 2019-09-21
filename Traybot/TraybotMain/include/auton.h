#include "vex.h"
#include "common.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

double squareDistance = 1.79;
double rightTurnDistance = 1.0;
//double fullTurnDistance = 2.0;

double distance1a = 1.2*squareDistance; //to pick up cubes
double distance1b = 0; //backward
double turn1a = 1.5; //turn to face zone
double distance1c = 0.5*squareDistance; //drive to zone
double distance1d = 0.5*squareDistance; //back away from zone

double distance2a = distance1a; //distance to 2nd cube
double distance2b = 1*squareDistance; //backward distance
double turn2a = rightTurnDistance; //turn toward cube
double distance2c = 0.8*squareDistance; //drive to cube
double turn2b = 0.5; //turn toward zone
double distance2d = 0.2*squareDistance; //drive to zone
double distance2e = distance2d;//back away from zone

void noAuton() {}


void red1() {
  spinIntake(100);
  basicEncoderDrive(50, distance1a, true); //drive and pick up cubes
  wait(100);

  spinIntake(0);
  basicEncoderDrive(50, -distance1b, true); //drive back
  wait(100);

  basicEncoderTurn(50, turn1a, true); //turn right to face zone
  wait(100);

  basicEncoderDrive(50, distance1c, true); //drive to zone
  wait(100);

  while(trayPot.value(vex::analogUnits::range12bit) > maxPotVal) {
    moveTray(60);
  }
  moveTray(0);
  wait(500);
  basicEncoderDrive(40, -distance1d, true);
}


void red2() {
  spinIntake(100);
  basicEncoderDrive(50, distance2a, true); // drive pick up 2 cubes
  wait(100);
  basicEncoderDrive(50, -distance2b, true); //drive back
  wait(100);
  basicEncoderTurn(50, -turn2a, true); //turn left
  wait(100);
  basicEncoderDrive(50, distance2c, true); //drive pick up cube
  wait(500);
  spinIntake(0);
  basicEncoderTurn(50, -turn2b, true); //turn to face zone
  basicEncoderDrive(50, distance2d, true); //drive to zone

  while(trayPot.value(vex::analogUnits::range12bit) > maxPotVal) {
    moveTray(50);
  }
  moveTray(0);
  wait(500);
  basicEncoderDrive(40, -distance2d, true);
}


void blue1() {
  spinIntake(100);
  basicEncoderDrive(50, distance1a, true); //drive and pick up cubes
  wait(100);

  spinIntake(0);
  basicEncoderDrive(50, -distance1b, true); //drive back
  wait(100);

  basicEncoderTurn(50, -turn1a, true); //turn left to face zone
  wait(100);

  basicEncoderDrive(50, distance1c, true); //drive to zone
  wait(100);

  while(trayPot.value(vex::analogUnits::range12bit) > maxPotVal) {
    moveTray(50);
  }
  moveTray(0);
  wait(500);
  basicEncoderDrive(40, -distance1d, true);
}


void blue2() {
  spinIntake(100);
  basicEncoderDrive(50, distance2a, true); // drive pick up 2 cubes
  wait(100);
  basicEncoderDrive(50, -distance2b, true); //drive back
  wait(100);
  basicEncoderTurn(50, turn2a, true); //turn right
  wait(100);
  basicEncoderDrive(50, distance2b, true); //drive pick up cube
  wait(500);
  spinIntake(0);
  basicEncoderTurn(50, turn2b, true); //turn right to face zone
  basicEncoderDrive(50, distance2c, true); //drive to zone

  while(trayPot.value(vex::analogUnits::range12bit) > maxPotVal) {
    moveTray(50);
  }
  moveTray(0);
  wait(500);
  basicEncoderDrive(40, -distance2d, true);
}


#include "vex.h"
#include "common.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

int distance1a = 0; //to pick up cubes
int distance1b = 0; //backward
int turn1a = 0; //turn to face zone
int distance1c = 0; //drive to zone
int distance1d = 0; //back away from zone

int distance2a = 0; //distance to cube
int turn2a = 0; //turn toward cube
int distance2b = 0; //drive to cube
int turn2b = 0; //turn toward zone
int distance2c = 0; //drive to zone
int distance2d = 0;//back away from zone

void noAuton() {}

void test() {
  timedDrive(35, 1000); //tester auton just to see if auton selection works
}


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
  basicEncoderDrive(50, distance2a, true); // drive pick up cube
  wait(100);
  basicEncoderTurn(50, -turn2a, true); //turn left
  wait(100);
  basicEncoderDrive(50, distance2b, true); //drive pick up cube
  wait(500);
  spinIntake(0);
  basicEncoderTurn(50, -turn2b, true); //turn to face zone
  basicEncoderDrive(50, distance2c, true); //drive to zone

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
  basicEncoderDrive(50, distance2a, true); // drive pick up cube
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


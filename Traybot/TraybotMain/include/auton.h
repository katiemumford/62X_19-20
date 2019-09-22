#include "vex.h"
#include "common.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

double squareDistance = 1.79;
double rightTurnDistance = 0.75;
//double fullTurnDistance = 2.0;

double distance1a = 3; //to pick up cubes
double distance1b = 3-1.133; //backward
double turn1a = 0.99; //turn to face zone
double distance1c = 1.91-1.139; //drive to zone
double distance1d = 2; //back away from zone

double distance2a = 1; //distance to  cube
double turn2a = 0.5; //turn toward cube
double distance2b = 2.269-0.7; //drive to cube
double turn2b = 0.5; //turn toward zone
double distance2c = 0.2*squareDistance; //drive to zone
double distance2d = distance2d;//back away from zone

void deployTray() {
  moveArm(100);
  wait(800);
  moveArm(-70);
  wait(800);
  moveArm(0);
}

void outtakeSome() {
spinIntake(-50);
  wait(300);
  spinIntake(0);
}

void noAuton() {
  deployTray();
}

void red1() {
  deployTray();
  
  spinIntake(100);
  basicEncoderDrive(48, distance1a, true); //drive and pick up cubes
  wait(690);

  basicEncoderDrive(50, -distance1b, true); //drive back
  wait(200);
  
  basicEncoderTurn(50, turn1a, true); //turn left to face zone
  wait(500);
  spinIntake(0);

  basicEncoderDrive(50, distance1c, true); //drive to zone
  wait(100);

  outtakeSome();

  while(trayPot.value(vex::analogUnits::range12bit) > maxPotVal) {
    moveTray(60);
  }
  moveTray(0);
  wait(500);
  
  basicEncoderDrive(40, -distance1d, true);
}


void red2() {
  deployTray();
  /*
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
  */
}


void blue1() {
  deployTray();
  
  spinIntake(100);
  basicEncoderDrive(48, distance1a, true); //drive and pick up cubes
  wait(690);

  basicEncoderDrive(50, -distance1b, true); //drive back
  wait(200);
  
  basicEncoderTurn(50, -turn1a, true); //turn left to face zone
  wait(500);
  spinIntake(0);

  basicEncoderDrive(50, distance1c, true); //drive to zone
  wait(100);

  outtakeSome();

  while(trayPot.value(vex::analogUnits::range12bit) > maxPotVal) {
    moveTray(60);
  }
  moveTray(0);
  wait(500);
  
  basicEncoderDrive(40, -distance1d, true);
}


void blue2() {
  deployTray();
  /*
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
  */
}

void test() {
  outtakeSome();
}


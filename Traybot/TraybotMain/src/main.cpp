#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "vex.h"
#include "config.h"
#include <cmath>
#include <vector>
using namespace vex;

struct Auton {
  void(*ref)();
  const char* name;
};

int minpct = 5;
int autonNum = 0;
std::vector<Auton> autons;

void drive(double l,  double r) {
  if (l < minpct && l > -minpct) { l = 0; }
  if (r < minpct && r > -minpct) { r = 0; }

  l1.spin(vex::directionType::fwd, l, vex::percentUnits::pct);
  l2.spin(vex::directionType::fwd, l, vex::percentUnits::pct);
  r1.spin(vex::directionType::fwd, r, vex::percentUnits::pct);
  r2.spin(vex::directionType::fwd, r, vex::percentUnits::pct);
}

void vdrive(double l, double r) {
  l *= 12.0/100;
  r *= 12.0/100;

  l1.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  l2.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  r1.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
  r2.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
}


/////DRIVER_HELPERS/////
#pragma region



#pragma endregion


/////AUTON_HELPERS//////
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


/////////AUTONS/////////
#pragma region

void noAuton() {}

void red1() {}

void red2() {}

void blue1() {}

void blue2() {}

#pragma endregion


////////PRE-AUTON////////
#pragma region

void drawButtons() {
  Brain.Screen.setFont(fontType::mono20);
  Brain.Screen.setPenColor(color::black);
  for (int i = 0; i < autons.size(); i++) {
    int x = (i > 4) ? (10 + 110*(i-4)) : (10 + 110*i);
    int y = (i > 4) ? 130 : 10;
    vex::color c = (autonNum == i) ? (color::green) : (color::blue);
    Brain.Screen.drawRectangle(x, y, 100, 100, c);
    Brain.Screen.printAt(x+25,y+45, autons[i].name);
  }
}

void screenPress(int xp, int yp) {
  for (int i = 0; i < autons.size(); i++) {
    int x = (i > 4) ? (10 + 110*(i-4)) : (10 + 110*i);
    int y = (i > 4) ? 130 : 10;
    if (xp >= x && xp <= x+100 && yp >= y && yp <= y+100) {
      autonNum = i;
      break;
    }
  }
}

void pre_auton( void ) {
  autons = {{noAuton, "No Auton"}, {red1, "Red 1"}, {red2, "Red 2"}, {blue1, "Blue 1"}, {blue2, "Blue 2"}};
  while (true) {
    if (Brain.Screen.pressing()) {
      screenPress(Brain.Screen.xPosition(), Brain.Screen.yPosition());
    }
    Brain.Screen.clearScreen();
    drawButtons();
    Brain.Screen.render();
    task::sleep(200);
  }
}
#pragma endregion


void usercontrol (void) {

  while (1) {
    vdrive(Controller.Axis3.value()*100/127, Controller.Axis2.value()*100/127);
    vex::task::sleep(20); 
  }
}

int main() {
    Competition.autonomous(autons[autonNum].ref);
    Competition.drivercontrol(usercontrol);
    
    pre_auton();
                              
    while(1) {
      vex::task::sleep(100);
    }    
       
}
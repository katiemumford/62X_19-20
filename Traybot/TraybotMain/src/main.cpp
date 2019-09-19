#include "vex.h"
#include "config.h"
#include <cmath>
#include <vector>
using namespace vex;

int minpct = 5;
int autonNum = 0;
std::vector<void (*)()> autons;
std::vector<const char*> autonNames;

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


/////////AUTONS/////////
#pragma region

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
  for (int i = 0; i < autonNames.size(); i++) {
    int x = (i > 4) ? (10 + 110*(i-4)) : (10 + 110*i);
    int y = (i > 4) ? 130 : 10;
    vex::color c = (autonNum == i) ? (color::green) : (color::blue);
    Brain.Screen.drawRectangle(x, y, 100, 100, c);
    Brain.Screen.printAt(x+25,y+45, autonNames[i]);
  }
}

void checkPress(int xp, int yp) {
  for (int i = 0; i < autonNames.size(); i++) {
    int x = (i > 4) ? (10 + 110*(i-4)) : (10 + 110*i);
    int y = (i > 4) ? 130 : 10;
    if (xp >= x && xp <= x+100 && yp >= y && yp <= y+100) {
      autonNum = i;
    }
  }
}

void pre_auton( void ) {
  autons = {red1, red2, blue1, blue2};
  autonNames = {"red1", "red2", "blue1", "blue2"};
  while (true) {
    if (Brain.Screen.pressing()) {
      checkPress(Brain.Screen.xPosition(), Brain.Screen.yPosition());
    }
    Brain.Screen.clearScreen();
    drawButtons();
    Brain.Screen.render();
    task::sleep(100);
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
    Competition.autonomous(autons[autonNum]);
    Competition.drivercontrol(usercontrol);
    
    pre_auton();
                              
    while(1) {
      vex::task::sleep(100);
    }    
       
}
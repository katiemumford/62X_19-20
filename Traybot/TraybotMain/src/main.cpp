#include "vex.h"
#include "auton.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

struct Auton {
  void(*ref)();
   const char* name;
};

int autonNum = 0;
std::vector<Auton> autons = {
  {noAuton, "No Auton"}, 
  {red1, "Red 1"}, 
  {red2, "Red 2"}, 
  {blue1, "Blue 1"}, 
  {blue2, "Blue 2"}
};

void drawButtons() {
  Brain.Screen.setPenColor(color::white);

  for (int i = 0; i < autons.size(); i++) {
    int x = (i > 3) ? (10 + 110*(i-4)) : (10 + 110*i);
    int y = (i > 3) ? 130 : 10;
    vex::color c = (autonNum == i) ? (color::green) : (color::blue);
    Brain.Screen.drawRectangle(x, y, 100, 100, c);
    Brain.Screen.printAt(x+15,y+45, autons[i].name);
  }
}

void screenPress(int xp, int yp) {
  for (int i = 0; i < autons.size(); i++) {
    int x = (i > 3) ? (10 + 110*(i-4)) : (10 + 110*i);
    int y = (i > 3) ? 130 : 10;
    if (xp >= x && xp <= x+100 && yp >= y && yp <= y+100) {
      autonNum = i;
      break;
    }
  }
}

void pre_auton( void ) {
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


void usercontrol (void) {
  while (1) {
    vdrive(Controller.Axis3.value()*100/127, Controller.Axis2.value()*100/127);
    intakeControl();
    armControl();
    trayControl();
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
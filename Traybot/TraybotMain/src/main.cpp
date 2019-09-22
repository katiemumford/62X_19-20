#include "vex.h"
#include "auton.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

//custom variable-type to define an autonomous program
struct Auton {  
  void(*ref)(); //function reference
  const char* name; //program name
};

int autonNum = 0; //the index (number) of the auton chosen
bool preAutonBool;

//array of auton programs
std::vector<Auton> autons = { 
  {noAuton, "No Auton"}, 
  {red1, "Red 1"},
  {red2, "Red 2"}, 
  {blue1, "Blue 1"}, 
  {blue2, "Blue 2"},
  {test, "test"}
};

//*draws the buttons on the Brain screen representing autons
void drawButtons() {  
  Brain.Screen.setPenColor(color::white);

  //goes through array and draws a button for each program
  for (int i = 0; i < autons.size(); i++) {

    //calculates each button's x and y position on screen
    int x = (i > 3) ? (16 + 116*(i-4)) : (16 + 116*i);  
    int y = (i > 3) ? 127 : 14; 

    //if auton is chosen, color its button green instead of blue
    vex::color c = (autonNum == i) ? (color::green) : (color::blue);  

    //display button and auton program name
    Brain.Screen.drawRectangle(x, y, 100, 99, c);
    Brain.Screen.printAt(x+15,y+45, autons[i].name);
  }
}

//*checks if an auton button was recently pressed on screen
void screenPress(int xp, int yp) {  

  //goes through array and checks button for each auton
  for (int i = 0; i < autons.size(); i++) {

    //calculates x and y positions of button for each auton
    int x = (i > 3) ? (16 + 116*(i-4)) : (16 + 116*i);
    int y = (i > 3) ? 127 : 14;

    //if the x and y coordinates of the screen press fall within the button,
    if (xp >= x && xp <= x + 100 && yp >= y && yp < y + 100) {
      autonNum = i; //make that auton the chosen auton
      break;
    }
  }
}

int pre_autonTask() { //the auton selection runs in pre-auton
  while (preAutonBool) {
    if (Brain.Screen.pressing()) {  //if screen is pressed, check if a button was pressed
      screenPress(Brain.Screen.xPosition(), Brain.Screen.yPosition());
    }
    drawButtons();
    Brain.Screen.render();
    task::sleep(200);
    Brain.Screen.clearScreen();
  }
  return 0;
}

void pre_auton( void ) {  
  preAutonBool = true;
  vex::task p(pre_autonTask);
}

void usercontrol (void) { 
  preAutonBool = false;
  vex::task::stop(pre_autonTask);
  Brain.Screen.clearScreen(vex::color::black); //stops pre auton and clears screen
  while (1) {
    vdrive(Controller.Axis3.value()*100/127.0, Controller.Axis2.value()*100/127.0);
    intakeControl();
    armControl();
    trayControl();
    vex::task::sleep(20); 
  }
}

void theAuton(void) {
  preAutonBool = false;
  autons[autonNum].ref();
}

int main() {
    Competition.autonomous(theAuton);
    Competition.drivercontrol(usercontrol);
    pre_auton();                        
    while(1) {
      vex::task::sleep(100);
    }        
}
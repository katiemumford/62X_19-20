#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_motorgroup.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_triport.h"
#include "vex.h"
#include <cmath>
#include <ratio>
#include <vector>
using namespace vex;

vex::brain Brain;
vex::competition Competition;
vex::controller Controller;

//drive motors
vex::motor r1 (vex::PORT13, true); 
vex::motor r2 (vex::PORT12, true);
vex::motor l1 (vex::PORT3, false);
vex::motor l2 (vex::PORT2, false);

vex::motor arm (vex::PORT4, false);
vex::motor tray (vex::PORT14, false);

//right and left intake motors
vex::motor rin (vex::PORT11, true);
vex::motor lin (vex::PORT1, false);

//potentiometer to measure tray's angle of elevation
vex::pot trayPot (Brain.ThreeWirePort.A);

//vex::gyro gyr (Brain.ThreeWirePort.B);
//vex::accelerometer acc (Brain.ThreeWirePort.C);






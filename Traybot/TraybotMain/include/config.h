#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_motorgroup.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_triport.h"
#include "vex.h"

vex::brain Brain;
vex::competition Competition;
vex::controller Controller;

//drive motors
vex::motor r1 (vex::PORT1, false); 
vex::motor r2 (vex::PORT2, false);
vex::motor l1 (vex::PORT3, true);
vex::motor l2 (vex::PORT4, true);

vex::motor arm (vex::PORT5, false);
vex::motor tray (vex::PORT6, false);

//right and left intake motors
vex::motor rin (vex::PORT7, false);
vex::motor lin (vex::PORT8, true);

vex::pot trayPot (Brain.ThreeWirePort.A);
//vex::gyro gyr (Brain.ThreeWirePort.B);
//vex::accelerometer acc (Brain.ThreeWirePort.C);
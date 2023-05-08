#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FL = motor(PORT16, ratio6_1, true);
motor BL = motor(PORT14, ratio6_1, true);
motor FR = motor(PORT17, ratio6_1, false);
motor BR = motor(PORT19, ratio6_1, false);
controller Controller1 = controller(primary);
motor Intake = motor(PORT10, ratio6_1, false);
motor cata = motor(PORT5, ratio36_1, false);
digital_out Expansion1 = digital_out(Brain.ThreeWirePort.A);
pot CatapultStop = pot(Brain.ThreeWirePort.B);
digital_out INDEXER = digital_out(Brain.ThreeWirePort.C);
motor FlywheelMotorA = motor(PORT12, ratio6_1, false);
motor FlywheelMotorB = motor(PORT11, ratio6_1, false);
motor_group Flywheel = motor_group(FlywheelMotorA, FlywheelMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
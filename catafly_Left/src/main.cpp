/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FL                   motor         5               
// ML                   motor         7               
// BL                   motor         9               
// FR                   motor         13              
// MR                   motor         10              
// BR                   motor         12              
// Inertial4            inertial      14              
// Controller1          controller                    
// Intake               motor         19              
// cata                 motor         16              
// Expansion1           digital_out   A               
// CatapultStop         pot           B               
// ---- END VEXCODE CONFIGURED DEVICES ----//   

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
//inertial Inertial4 = inertial(PORT14);
inertial Inertial4 = inertial(PORT14);
motor_group Left(FL, ML, BL);
motor_group Right(FR, MR, BR);
//const double wheelTravel = 10.24; 
//const double trackWidth =12.75;
//const double wheelBase = 9.75;
const double gearRatio = 0.6;

smartdrive HDRIVE( Left, Right, Inertial4, 10.24, 12.75, 9.75, distanceUnits::in, gearRatio);


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial4.calibrate();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  Left.setVelocity(40,percent);
  Right.setVelocity(40,percent);
  HDRIVE.setTurnVelocity(10,percent);
  HDRIVE.driveFor(forward,2,inches);
  Intake.spinFor(reverse,35,degrees);
  HDRIVE.driveFor(reverse,3,inches);
  HDRIVE.turnFor(right,37,degrees);
  HDRIVE.driveFor(reverse,45,inches, false);
  wait(1.7, sec);
  HDRIVE.stop();
  Left.setVelocity(60,percent);
  Right.setVelocity(60,percent);
  HDRIVE.setTurnVelocity(50,percent);
  wait(0.5,sec);
  HDRIVE.turnFor(left,54,degrees);
  wait(0.5,sec);
  HDRIVE.driveFor(reverse,2,inches);
  wait(1,sec);
  cata.setVelocity(100,pct);
  cata.spinFor(reverse,900,degrees);
  wait(0.5,sec);
  HDRIVE.driveFor(forward,3,inches);
 
  // ..........................................................................
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void LaunchDisk(void){
  
  cata.spinFor(reverse, 100, degrees); 
}

void Expansion(){

  Expansion1.set(true);
  wait(0.5,sec);
  Expansion1.set(false);
  

}



void usercontrol(void) {
  // User control code here, inside the loop
  Controller1.ButtonY.pressed(Expansion);
  cata.setVelocity(100, pct);
  while (1) {

  
  Brain.Screen.print(CatapultStop.angle(degrees));
  Brain.Screen.newLine(); 


  if ((CatapultStop.angle(degrees) > 20.5)){
      cata.spin(reverse);
  } else if ((CatapultStop.angle(degrees) <= 20.5)){
      cata.stop(hold);
      if (Controller1.ButtonA.pressing()){
          LaunchDisk();
      }    
    }
    
    
   
    ///////////////////////
    Left.spin(forward,Controller1.Axis3.value(), pct);
    Right.spin(forward,Controller1.Axis2.value(),pct);
    
    if(Controller1.ButtonR1.pressing()) {
      Intake.setVelocity(100,percent);
      Intake.spin(forward);
    }
    else if(Controller1.ButtonR2.pressing()) {
      Intake.setVelocity(100,percent);
      Intake.spin(reverse);
     
    }
    
    

     else{
      Intake.stop();
    }
    
    if(Controller1.ButtonL1.pressing()) {
      cata.setVelocity(100,percent);
      cata.spin(reverse);
    }
    else if(Controller1.ButtonL2.pressing()) {
      cata.setVelocity(100,percent);
      cata.stop();
     
    }
    
    
    
     
    

    
  
    cata.setStopping(brake);  
      

    
    
    
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

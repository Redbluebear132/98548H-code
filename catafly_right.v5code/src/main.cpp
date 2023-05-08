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
// BL                   motor         9               
// FR                   motor         13              
// BR                   motor         12              
// Controller1          controller                    
// Intake               motor         19              
// cata                 motor         16              
// Expansion1           digital_out   A               
// CatapultStop         pot           B               
// Catapneumatic        digital_out   C               
// Flywheel             motor_group   11, 6          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
//inertial Inertial4 = inertial(PORT4);
motor_group Left(FL,BL);
motor_group Right(FR,BR);
const double wheelTravel = 10.24; 
const double trackWidth =12.75;
const double wheelBase = 9.75;
const double gearRatio = 0.78;
double val;
//drivetrain HDRIVE(Left, Right, wheelTravel, trackWidth, wheelBase, distanceUnits::in, gearRatio);

inertial seer = inertial(PORT9);
smartdrive HDRIVE(Left, Right, seer, wheelTravel, trackWidth, wheelBase, distanceUnits::in, gearRatio);


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit(); 
  seer.calibrate();
  wait(3,sec);
  HDRIVE.setTurnConstant(.3);
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

   //ROLLER DRIVE AND VELOCITY SET
  Left.setVelocity(50,percent);
  Right.setVelocity(50,percent);
  Intake.setVelocity(100,percent);
  HDRIVE.setTurnVelocity(40,percent);
  Catapneumatic.set(true);
  HDRIVE.driveFor(forward, 24, inches);
  HDRIVE.turnFor(right, 93.5,degrees);
  //TURNING AND DRIVING INTO ROLLER
  HDRIVE.driveFor(forward,5.9,inches);
  wait(.5,sec);
  Intake.spinFor(reverse, 70, degrees,false);
  Left.setVelocity(60,percent);
  Right.setVelocity(60,percent);
  wait(.5,sec);
  HDRIVE.driveFor(reverse,4.5,inches);
  //TO MIDDLE
  HDRIVE.turnFor(left,46,degrees);
  HDRIVE.driveFor(reverse,70,inches,false);
  wait(2.1,sec);
  //SHOOTING
  HDRIVE.turnFor(right,82, degrees);
  wait(.3,sec);
  HDRIVE.setDriveVelocity(30,percent);
  HDRIVE.driveFor(reverse,9,inches,false);
  //wait(0.05,sec);
  cata.setVelocity(100,percent);
  cata.spinFor(reverse,908,degrees);
  Intake.spin(forward);
  wait(1.4,sec);
  cata.spinFor(reverse,900,degrees);
  Intake.stop();
  Catapneumatic.set(false);
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
  wait(0.1,sec);
  Expansion1.set(false);
}

void Indexer(){
  INDEXER.set(true);
  wait(0.5,sec);
  INDEXER.set(false);
}


void Flywheel90(){
  Flywheel.setVelocity(90,pct);
  Flywheel.spin(forward);
}

void FlywheelSTOP(){
  Flywheel.stop();
}
void usercontrol(void) {
  
  INDEXER.set(false);
  Controller1.ButtonY.pressed(Expansion);
  cata.setVelocity(100, pct);
  
  while (1) {
  Brain.Screen.setPenWidth(1);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(CatapultStop.angle(degrees));
  Brain.Screen.setCursor(5, 20);
  Brain.Screen.setPenWidth(10);
  Brain.Screen.print(CatapultStop.angle(degrees));
  Controller1.ButtonDown.pressed(FlywheelSTOP);
  Controller1.ButtonLeft.pressed(Flywheel90);
  Controller1.ButtonB.pressed(Indexer);
  
  if (Controller1.ButtonA.pressing()){
    LaunchDisk();
  }    

  if (CatapultStop.angle(degrees) > 151){
    cata.spin(reverse);
  } 
  else if (CatapultStop.angle(degrees) <= 151){
    cata.stop(hold);
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
    Brain.Screen.clearScreen();
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

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
// FL                   motor         15              
// BL                   motor         14              
// FR                   motor         17              
// BR                   motor         4               
// Controller1          controller                    
// Intake               motor         7               
// cata                 motor         5               
// Expansion1           digital_out   A               
// CatapultStop         pot           B               
// INDEXER              digital_out   C               
// Flywheel             motor_group   12, 20          
// Expansion2           digital_out   H               
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
    Flywheel.spin(forward, 10.2, volt);
  Left.setVelocity(80,pct);
  Right.setVelocity(80,pct);
  HDRIVE.setTurnVelocity(30,pct);
  Intake.setVelocity(95,pct);
  HDRIVE.driveFor(forward,31,inches);
  HDRIVE.turnFor(right,90,degrees);
  HDRIVE.driveFor(forward,6.6,inches,false);
  wait(1.2,sec);
  Intake.spinFor(reverse,180,degrees,false);
  wait(0.5,sec);
  HDRIVE.driveFor(reverse,2,inches);
  //HDRIVE.turnFor(right,3.4,degrees);
  //wait(.5,sec);
  //INDEXER.set(true);
  //wait(0.3,sec);
  //INDEXER.set(false);
 // Flywheel.spin(forward,12,volt);
 // wait(1.5,sec);
 // INDEXER.set(true);
 // wait(0.4,sec);
 // INDEXER.set(false);
 // Flywheel.spin(forward,10.2,volt);
  HDRIVE.turnFor(right,123.4,degrees);
  Left.setVelocity(65,pct);
  Right.setVelocity(65,pct);
  Intake.spin(forward);
  HDRIVE.driveFor(forward,40,inches);
  HDRIVE.turnFor(left,107,degrees);
  wait(0.5,sec);
  INDEXER.set(true);
  wait(0.3,sec);
  INDEXER.set(false);
  wait(1.2,sec);
  INDEXER.set(true);
  wait(0.3,sec);
  INDEXER.set(false);
  wait(1.2,sec);
  INDEXER.set(true);
  wait(0.3,sec);
  INDEXER.set(false);
  Flywheel.stop();
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

void Expansion_1(){
  Expansion1.set(true);
  wait(0.1,sec);
  Expansion1.set(false);
}

void Expansion_2(){
  Expansion2.set(true);
  wait(0.1,sec);
  Expansion2.set(false);
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
  Controller1.ButtonY.pressed(Expansion_1);
  Controller1.ButtonRight.pressed(Expansion_2);
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

  if (CatapultStop.angle(degrees) > 152){
    cata.spin(reverse);
  } 
  else if (CatapultStop.angle(degrees) <= 152){
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

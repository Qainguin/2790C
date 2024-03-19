/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       vcs                                                       */
/*    Created:      3/18/2024, 2:18:56 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller Controller;
brain Brain;

// define your global instances of motors and other devices here

motor l1 = motor(11, true);
motor l2 = motor(12, true);
motor l3 = motor(13, true);

motor r1 = motor(18);
motor r2 = motor(19);
motor r3 = motor(20);

// Grouping all the drivetrain motors.

motor_group all_drive_motors = motor_group(l1,l2,l3,r1,r2,r3);

motor_group left_drive_motors = motor_group(l1,l2,l3);
motor_group right_drive_motors = motor_group(r1,r2,r3);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

// A function that moves the drivetrain forwards and backwards by the x_strength parameter.
// It also turns left and right by the y_strength parameter.
void move_drivetrain(float x_strength, float y_strength) {
  all_drive_motors.spin(fwd);
  left_drive_motors.setVelocity(y_strength, pct);
  right_drive_motors.setVelocity(y_strength, pct);
  
  if (x_strength) {
    left_drive_motors.setVelocity(y_strength-x_strength, pct);
    right_drive_motors.setVelocity(y_strength+x_strength, pct);
  }
}

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  all_drive_motors.setStopping(brake);

  Brain.Screen.setPenColor(white);

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(10,10,460,222);

  Brain.Screen.setPenColor(black);
  Brain.Screen.setFont(mono20);

  Brain.Screen.printAt(Brain.Screen.getStringWidth("This is centered"), 136, "This is centered");
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (true) {
    move_drivetrain(-Controller.Axis1.position(),-Controller.Axis3.position()); // Move and turn the drivetrain.

    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
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

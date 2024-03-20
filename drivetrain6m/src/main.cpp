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

// A function that moves the drivetrain forwards and backwards by the x_strength parameter.
// It also turns left and right by the y_strength parameter.

// For the parameters, use opposites (eg. forward = -100, backward = 100).
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
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  move_drivetrain(-100,0);
  wait(1, sec);
  move_drivetrain(0,0);
}

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

#include "main.h"
#include "helpers.hpp"

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///
void drive_example() {
  ez::Piston clamp('H', false);
  ez::Piston intakeLift('F', false);

  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_turn_relative_set(-50_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, 40, true);
  chassis.pid_wait();

  clamp.set(true);
  pros::delay(1000);

  conveyor.move(-30);
  pros::delay(700);
  conveyor.brake();

  // chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  // chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 110, 45);
  chassis.pid_wait();

  conveyor.move(127);
  intake.move(127);

  pros::delay(500);

  chassis.pid_drive_set(18_in, 40);
  chassis.pid_wait();

  // conveyor.move(-127);
  // pros::delay(500);

  // conveyor.move(127);
  // intake.move(127);

  pros::delay(1000);

  conveyor.brake();
  intake.brake();

  chassis.pid_drive_set(-6_in, 70, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(44_in, 100, true);
  chassis.pid_wait();

  conveyor.move(127);
  intake.move(127);

  chassis.pid_drive_set(10_in, 40, true);
  chassis.pid_wait();

  pros::delay(2000);

  conveyor.brake();
  intake.brake();

  // chassis.pid_drive_set(6_in, 40, true);
  // chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  intakeLift.set(true);
  pros::delay(1000);

  conveyor.move(127);
  intake.move(127);
  chassis.pid_drive_set(26_in, 40, true);
  chassis.pid_wait();

  pros::delay(2000);

  intake.brake();
  conveyor.brake();

}

///
// Turn Example
///
void turn_example() {
  ez::Piston clamp('H', false);
  ez::Piston intakeLift('E', false);


  chassis.pid_drive_set(-16_in, 80, true);
  chassis.pid_wait();



  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-48_in, 50, true);
  chassis.pid_wait();

  clamp.set(true);

  conveyor.move(-40);
  pros::delay(1000);
  conveyor.brake();

  intake.move(127);
  conveyor.move(127);
  
  chassis.pid_turn_relative_set(30_deg, TURN_SPEED);
  chassis.pid_wait();
  
  chassis.pid_drive_set(20_in, 40, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-30_deg, TURN_SPEED);
  chassis.pid_wait();

  intake.brake();
  conveyor.brake();

  chassis.pid_drive_set(36_in, 80, true);
  chassis.pid_wait();

  intake.move(127);
  conveyor.move(127);

  chassis.pid_swing_relative_set(ez::RIGHT_SWING, -90_deg, 60, 15);
  chassis.pid_wait();

  pros::delay(1000);

  intakeLift.set(true);

  chassis.pid_drive_set(20_in, 30, true);
  chassis.pid_wait();

  intakeLift.set(false);

  chassis.pid_drive_set(-34_in, 30, true);
  chassis.pid_wait();

  intake.brake();
  conveyor.brake();


  // pros::delay(500);




  // intake.brake();
  // conveyor.brake();

  // chassis.pid_drive_set(-34_in, 100, true);
  // chassis.pid_wait();

  // chassis.pid_turn_relative_set(85_deg, TURN_SPEED);
  // chassis.pid_wait();


  // chassis.pid_drive_set(-90_in, 100, true);
  // chassis.pid_wait();

  

}

///
// Combining Turn + Drive
///
void skills() {
  chassis.drive_angle_set(180_deg);

  chassis.pid_swing_relative_set(ez::LEFT_SWING, -40_deg, SWING_SPEED, 55);
  chassis.pid_wait();

  // intakeInitialize();

  chassis.pid_drive_set(-32_in, 50, true);
  // chassis.pid_wait_until(-15_in);
  // chassis.pid_speed_max_set(40);  
  chassis.pid_wait();

  pros::delay(200);

  clampIn();

  pros::delay(200);


  chassis.pid_drive_set(2_in, 50, true);
  chassis.pid_wait();


  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  groupStart(127);

  chassis.pid_drive_set(20_in, 50, true);
  chassis.pid_wait_until(10_in);
  chassis.pid_speed_max_set(40);  
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(-20_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(28_in, 50, true);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 55);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(15_in, 50, true);
  chassis.pid_wait();

  pros::delay(100);

  chassis.pid_drive_set(-15_in, 50, true);
  chassis.pid_wait();

  groupStop();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 30);
  chassis.pid_wait();
  
  

}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .
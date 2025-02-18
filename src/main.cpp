#include "main.h"
#include "pros/misc.h"
#include "subsystems.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-11, -12, -13, -14, -15},  // Left Chassis Ports (negative port will reverse it!)
    {1, 2, 3, 4, 5},            // Right Chassis Ports (negative port will reverse it!)

    21,    // IMU Port
    2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    600);  // Wheel RPM

void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(2);     // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(3, 3);      // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      // Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

void opcontrol() {
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_HOLD;

  chassis.drive_brake_set(driver_preference_brake);

  // ez::Piston lift('G', false);
  // // ez::Piston clamp('H', false);
  // ez::Piston doinker('F', false);
  // ez::Piston intakeLift('E', false);

  bool liftDeployed = false;
  bool clampDeployed = false;
  bool doinkerDeployed = false;
  bool intakeLiftDeployed = true;

  bool lift_positioning = false;
  bool color_sorting = false;

  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  conveyor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  while (true) {
    // chassis.opcontrol_tank();  // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT);  // Standard split arcade

    if (master.get_digital_new_press(DIGITAL_DOWN)) {
      liftDeployed = !liftDeployed;
      lift.set(liftDeployed);
    }

    if (master.get_digital_new_press(DIGITAL_Y)) {
      clampDeployed = !clampDeployed;
      clampPiston.set(clampDeployed);
    }

    if (master.get_digital_new_press(DIGITAL_B)) {
      doinkerDeployed = !doinkerDeployed;
      doinker.set(doinkerDeployed);
    }

    if (master.get_digital_new_press(DIGITAL_RIGHT)) {
      intakeLiftDeployed = !intakeLiftDeployed;
      intakeLift.set(intakeLiftDeployed);
    }

    if (master.get_digital(DIGITAL_R1)) {
      intake.move(127);
      conveyor.move(127);
    } else if (master.get_digital(DIGITAL_R2)) {
      intake.move(-127);
      conveyor.move(-127);
    } else {
      intake.brake();
      conveyor.brake();
    }

    double hue = color.get_hue();

    if (master.get_digital_new_press(DIGITAL_L1)) {
      lift_positioning = !lift_positioning;
        master.rumble(".");
    }

    if (master.get_digital_new_press(DIGITAL_L2)) {
      color_sorting = !color_sorting;
        master.rumble(". .");
    }

    master.set_text(0, 0, "Co: " + std::to_string(color_sorting) + " L: " + std::to_string(lift_positioning) + " Cl: "+std::to_string(clampDeployed));
    
    if (color_sorting) {
      lift_positioning = false;
        color.set_led_pwm(100);
      if (red_side) {
        if (hue > 100 && hue < 220) {   
          pros::delay(100);
          conveyor.move(-127);
          pros::delay(200);
        }
      } else if (red_side == false) {
        if (hue > 0 && hue < 20) {
        }
      }
    } else if (lift_positioning) {
      color_sorting = false;
      color.set_led_pwm(100);
      if (red_side) {
        if (hue > 0 && hue < 20) {
          conveyor.brake();
          conveyor.move(-80);
          pros::delay(100);
          conveyor.brake();
          lift_positioning = false;
        }
      } else if (red_side == false) {
        if (hue > 100 && hue < 220) {
          conveyor.brake();
          conveyor.move(-80);
          pros::delay(100);
          conveyor.brake();
          lift_positioning = false;
        }
      }
    } else {
      color.set_led_pwm(0);
    }
    
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
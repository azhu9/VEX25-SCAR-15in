#pragma once

#include "api.h"
// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::MotorGroup intake({9,});
inline pros::MotorGroup conveyor({-19, 20});

inline pros::Optical color(10);
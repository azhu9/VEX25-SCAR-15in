#pragma once

#include "api.h"
// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::MotorGroup intake({7, -16});
inline pros::Optical color(10);

#pragma once

#include "EZ-Template/piston.hpp"
#include "api.h"
// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::MotorGroup intake({16,});
inline pros::MotorGroup conveyor({-19, 7});

inline pros::Optical color(10);

inline ez::Piston clampPiston('H', false);
inline ez::Piston wallstakeLift('G', false);
inline ez::Piston doinker('F', false);
inline ez::Piston intakeLift('E', false);

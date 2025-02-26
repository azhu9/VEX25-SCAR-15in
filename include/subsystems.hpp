#pragma once

#include "EZ-Template/piston.hpp"
#include "api.h"
#include "pros/optical.hpp"
// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::Motor intake(-17);
inline pros::Motor conveyor(18);
inline pros::Rotation lb_rotation(15);
inline pros::Motor ladyBrown(14);

inline pros::Optical color(19);

inline int position = lb_rotation.get_position();

inline ez::Piston clampPiston('D', false);
inline ez::Piston leftDoinker('B', false);
inline ez::Piston rightDoinker('C', false);
inline ez::Piston intakeLift('A', false);
inline ez::Piston flipperPiston('E', false);
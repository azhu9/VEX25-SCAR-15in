#pragma once
#include "api.h"
#include "subsystems.hpp"

// // Drive constants for Autons
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;


//intake helper methods
inline void intakeStart(int voltage){
    intake.move(voltage);
}

inline void intakeStart(int voltage, int ms){
    intake.move(voltage);
    pros::delay(ms);
    intake.brake();
}

inline void intakeStop(){
    intake.brake();
}

//conveyor helper methods
inline void conveyorStart(int voltage){
    conveyor.move(voltage);
}


inline void conveyorStart(int voltage, int ms){
    conveyor.move(voltage);
    pros::delay(ms);
    conveyor.brake();
}

inline void conveyorStop(){
    conveyor.brake();
}

inline void groupStart(int voltage){
    intake.move(voltage);
    conveyor.move(voltage);
}


inline void groupStart(int voltage, int ms){
    intake.move(voltage);
    conveyor.move(voltage);
    pros::delay(ms);
    intake.brake();
    conveyor.brake();
}

inline void groupStop(){
    intake.brake();
    conveyor.brake();
}

inline void clampIn(){
    clampPiston.set(true);
}

inline void clampOut(){
    clampPiston.set(false);  //default position
}

inline void wallstakeLiftOut(){
    wallstakeLift.set(true);
}

inline void wallstakeLiftIn(){
    wallstakeLift.set(false);  //default position
}

inline void donkerOut(){ 
    doinker.set(true);
}

inline void donkerIn(){
    doinker.set(false);  //default position
}

//intake should be out for the rest of the match
inline void intakeLiftOut(){
    intakeLift.set(true); //default position
}

inline void intakeLiftIn(){
    intakeLift.set(false);
}

inline void intakeInitialize(){ //Use this at the beginning of autos 
    conveyor.move(-30);
    pros::delay(700);
    conveyor.brake();
}




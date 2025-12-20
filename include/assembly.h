#pragma once

#include "vex.h"

using namespace vex;

enum lift_positions : int { IDLE = 229, LOADING = 206, SCORING = 99 };

class Assembly {
public:
    Assembly(
        mik::motor intake_motor1,
        mik::motor intake_motor2, 
        mik::piston third_stage_1,
        mik::piston third_stage_2,
        mik::piston matchload,
        mik::piston left_wing
    );
    
    void init();
    void control();

    void intake_motors_control();
    void Sovereign_piston_control();
    
    mik::motor intake_motor1;
    mik::motor intake_motor2;
    mik::piston third_stage_1;
    mik::piston third_stage_2;
    mik::piston matchload;
    mik::piston left_wing;
   
    bool third_stage_1_open = false; bool third_stage_2_open = false; bool leftwing_open = false; bool matchload_open = false;
};
#pragma once

#include "vex.h"

using namespace vex;

enum lift_positions : int { IDLE = 229, LOADING = 206, SCORING = 99 };

class Assembly {
public:
    Assembly(
        mik::motor intake_motor1,
        mik::motor intake_motor2, 
        mik::piston middle_goal,
        mik::piston matchload,
        mik::piston left_wing,
        mik::piston right_wing
    );
    
    void init();
    void control();

    void intake_motors_control();
    void Sovereign_piston_control();

    int lift_arm_position = IDLE;
    vex::task lift_task;
    
    mik::motor intake_motor1;
    mik::motor intake_motor2;
    mik::piston middle_goal;
    mik::piston matchload;
    mik::piston left_wing;
    mik::piston right_wing;
    bool middle_open = false; bool rightwing_open = false; bool leftwing_open = false; bool matchload_open = false;
};
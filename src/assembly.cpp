#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
    mik::motor intake_motor1, 
    mik::motor intake_motor2,
    mik::piston third_stage_1,
    mik::piston third_stage_2,
    mik::piston matchload,
    mik::piston left_wing
) :
    // Assign the ports to the devices
    intake_motor1(intake_motor1),
    intake_motor2(intake_motor2),
    third_stage_1(third_stage_1),
    third_stage_2(third_stage_2),
    matchload(matchload),
    left_wing(left_wing) // Make sure when using a 3 wire device that isnt mik::piston you convert the port. `to_triport(PORT_A)`.
{};

// You want to call this function once in the user control function in main.
void Assembly::init() {
    // Create the task to move the lift arm. We only want one task to be created
   
    // To stop the task do `assembly.lift_task.stop();`
} 

// You want to put this function inside the user control loop in main.
void Assembly::control() {
    intake_motors_control();
    Sovereign_piston_control();
}


// Spins intake forward if L1 is being held, reverse if L2 is being held; stops otherwise
void Assembly::intake_motors_control() {
    if(Controller.ButtonR1.pressing()){
        third_stage_1.set(true);
        intake_motor1.spin(fwd, 12, volt);
        intake_motor2.spin(fwd, 12, volt);
    }
    else if(Controller.ButtonR2.pressing()){
        third_stage_1.set(false);
        intake_motor1.spin(fwd, 12, volt);
        intake_motor2.spin(fwd , 12, volt);
    }
    else if(Controller.ButtonL1.pressing()){
        intake_motor1.spin(reverse, 12, volt);
        intake_motor2.spin(reverse, 5, volt);
    }
    else if(Controller.ButtonL2.pressing()){
        third_stage_2.set(true);
        intake_motor1.spin(fwd, 12, volt);
        intake_motor2.spin(fwd, 12, volt);
    }
    else{
        intake_motor1.stop();
        intake_motor2.stop();
        third_stage_2.set(false);
    }
}


// Extends or retracts piston when button A is pressed, can only extend or retract again until button A is released and pressed again*/
/*void Assembly::Sovereign_piston_control() {
   if (Controller.ButtonB.pressing()) {
    middle_goal.set(true);
} else {
    middle_goal.set(false);
}

if (Controller.ButtonY.pressing()) {
    right_wing.set(true);
} else {
    right_wing.set(false);
}

if (Controller.ButtonRight.pressing()) {
    left_wing.set(true);
} else {
    left_wing.set(false);
}

if (Controller.ButtonDown.pressing()) {
    matchload.set(true);
} else {
    matchload.set(false);
}*/

void Assembly::Sovereign_piston_control() {



    // --- Middle Goal (Button B) ---
    static bool B_last = false;
    if (Controller.ButtonB.pressing() && !B_last) {
    

        third_stage_1_open = !third_stage_1_open;
        third_stage_1.set(third_stage_1_open);

        third_stage_2_open = !third_stage_2_open;
        third_stage_2.set(third_stage_2_open);

    }
    B_last = Controller.ButtonB.pressing();

    // --- Left Wing (Button Right) ---
    static bool Right_last = false;
    if (Controller.ButtonRight.pressing() && !Right_last) {
        leftwing_open = !leftwing_open;
        left_wing.set(leftwing_open);
    }
    Right_last = Controller.ButtonRight.pressing();

    // --- Matchload (Button Down) ---
    static bool Down_last = false;
    if (Controller.ButtonDown.pressing() && !Down_last) {
        matchload_open = !matchload_open;
        matchload.set(matchload_open);
    }
    Down_last = Controller.ButtonDown.pressing();
}

#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
    mik::motor intake_motor1, 
    mik::motor intake_motor2,
    mik::piston middle_goal,
    mik::piston matchload,
    mik::piston right_wing,
    mik::piston left_wing
) :
    // Assign the ports to the devices
    intake_motor1(intake_motor1),
    intake_motor2(intake_motor2),
    middle_goal(middle_goal),
    matchload(matchload),
    right_wing(right_wing),
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
        intake_motor1.spin(reverse, 12, volt);
    }
    else if(Controller.ButtonR2.pressing()){
        intake_motor1.spin(reverse, 12, volt);
        intake_motor2.spin(reverse, 12, volt);
    }
    else if(Controller.ButtonL1.pressing()){
        intake_motor1.spin(reverse, 12, volt);
        intake_motor2.spin(reverse, 12, volt);
    }
    else if(Controller.ButtonL2.pressing()){
        intake_motor1.spin(fwd, 12, volt);
    }
    else{
        intake_motor1.stop();
        intake_motor2.stop();
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
        middle_open = !middle_open;
        middle_goal.set(middle_open);
    }
    B_last = Controller.ButtonB.pressing();

    // --- Right Wing (Button Y) ---
    static bool Y_last = false;
    if (Controller.ButtonY.pressing() && !Y_last) {
        rightwing_open = !rightwing_open;
        right_wing.set(rightwing_open);
    }
    Y_last = Controller.ButtonY.pressing();

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

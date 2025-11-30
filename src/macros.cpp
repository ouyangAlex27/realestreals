#include "vex.h"

using namespace vex;
using namespace mik;


void intake(void){
    assembly.intake_motor1.spin(fwd, 12, volt);
}

void top_goal(void){
    assembly.intake_motor1.spin(fwd, 12, volt);
    assembly.intake_motor2.spin(reverse, 12, volt);
}

void bottom_goal(void){
    assembly.intake_motor1.spin(reverse, 12, volt);
}

void pause_actions(void){
    assembly.intake_motor1.stop();
    assembly.intake_motor2.stop();
}
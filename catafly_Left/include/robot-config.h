using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FL;
extern motor ML;
extern motor BL;
extern motor FR;
extern motor MR;
extern motor BR;
extern inertial Inertial4;
extern controller Controller1;
extern motor Intake;
extern motor cata;
extern digital_out Expansion1;
extern pot CatapultStop;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
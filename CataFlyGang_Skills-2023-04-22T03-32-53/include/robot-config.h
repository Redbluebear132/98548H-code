using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FL;
extern motor BL;
extern motor FR;
extern motor BR;
extern controller Controller1;
extern motor Intake;
extern motor cata;
extern digital_out Expansion1;
extern pot CatapultStop;
extern digital_out INDEXER;
extern motor_group Flywheel;
extern digital_out Expansion2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
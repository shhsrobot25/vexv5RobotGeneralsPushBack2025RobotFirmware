#include "main.h"

#define LEFT_WHEELS_PORT 15
#define RIGHT_WHEELS_PORT -13
#define FEEDER_PORT 1
#define EXTRUDER_LIFT_A_PORT 2
#define EXTRUDER_LIFT_B_PORT 7
#define EXTRUDER_LOWER_PORT 4
#define EXTRUDER_MIDDLE_PORT 5
#define EXTRUDER_UPPER_PORT 3
#define EXTRUDER_TOP_PORT 6

void opcontrol() {
    pros::Controller master(CONTROLLER_MASTER);
    pros::Controller partner(CONTROLLER_PARTNER);

    pros::Motor left_wheels(LEFT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor right_wheels(RIGHT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor feeder(FEEDER_PORT, pros::v5::MotorGears::green);
    pros::MotorGroup extruder_lift({EXTRUDER_LIFT_A_PORT, EXTRUDER_LIFT_B_PORT}, pros::v5::MotorGears::green);
    pros::Motor extruder_lower(EXTRUDER_LOWER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_middle(EXTRUDER_MIDDLE_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_upper(EXTRUDER_UPPER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_top(EXTRUDER_TOP_PORT, pros::v5::MotorGears::green);

    bool driverReverse = false;

    while (true) {
        // master controls
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !driverReverse) {
            driverReverse = true;
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && driverReverse) {
            driverReverse = false;
        }
        if (driverReverse) {
            left_wheels.move(master.get_analog(ANALOG_LEFT_Y) * -1);
            right_wheels.move(master.get_analog(ANALOG_RIGHT_Y) * -1);
        } else {
            left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
            right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));
        }

        // reversable partner controls
        if (!partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
                feeder.move(127);
            } else {
                feeder.move(0);
            }
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                extruder_lift.move(127);
                extruder_lower.move(-127);
                extruder_middle.move(0);
                extruder_upper.move(0);
                extruder_top.move(0);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                extruder_lift.move(127);
                extruder_lower.move(127);
                extruder_middle.move(127);
                extruder_upper.move(-127);
                extruder_top.move(0);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                extruder_lift.move(127);
                extruder_lower.move(127);
                extruder_middle.move(127);
                extruder_upper.move(127);
                extruder_top.move(-127);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                extruder_lift.move(127);
                extruder_lower.move(127);
                extruder_middle.move(127);
                extruder_upper.move(127);
                extruder_top.move(127);
            } else {
                extruder_lift.move(0);
                extruder_lower.move(0);
                extruder_middle.move(0);
                extruder_upper.move(0);
                extruder_top.move(0);
            }
        } else {
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
                feeder.move(-127);
            } else {
                feeder.move(0);
            }
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                extruder_lift.move(-127);
                extruder_lower.move(127);
                extruder_middle.move(0);
                extruder_upper.move(0);
                extruder_top.move(0);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                extruder_lift.move(-127);
                extruder_lower.move(-127);
                extruder_middle.move(-127);
                extruder_upper.move(127);
                extruder_top.move(0);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                extruder_lift.move(-127);
                extruder_lower.move(-127);
                extruder_middle.move(-127);
                extruder_upper.move(-127);
                extruder_top.move(127);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                extruder_lift.move(-127);
                extruder_lower.move(-127);
                extruder_middle.move(-127);
                extruder_upper.move(-127);
                extruder_top.move(-127);
            } else {
                extruder_lift.move(0);
                extruder_lower.move(0);
                extruder_middle.move(0);
                extruder_upper.move(0);
                extruder_top.move(0);
            }
        }

        pros::delay(2);
    }
}

void autonomous() {
    pros::Motor left_wheels(LEFT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor right_wheels(RIGHT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor feeder(FEEDER_PORT, pros::v5::MotorGears::green);
    pros::MotorGroup extruder_lift({EXTRUDER_LIFT_A_PORT, EXTRUDER_LIFT_B_PORT}, pros::v5::MotorGears::green);
    pros::Motor extruder_lower(EXTRUDER_LOWER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_middle(EXTRUDER_MIDDLE_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_upper(EXTRUDER_UPPER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_top(EXTRUDER_TOP_PORT, pros::v5::MotorGears::green);
}
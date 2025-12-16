#include "main.h"

#define LEFT_WHEELS_PORT 2
#define RIGHT_WHEELS_PORT -1
#define FEEDER_PORT -3
#define EXTRUDER_LIFT_PORT 17
#define EXTRUDER_LOWER_PORT -16
#define EXTRUDER_MIDDLE_PORT -19
#define EXTRUDER_UPPER_PORT -20
#define PI 3.14159265359

void opcontrol() {
    pros::Controller master(CONTROLLER_MASTER);
    pros::Controller partner(CONTROLLER_PARTNER);

    pros::Motor left_wheels(LEFT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor right_wheels(RIGHT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor feeder(FEEDER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_lift(EXTRUDER_LIFT_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_lower(EXTRUDER_LOWER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_middle(EXTRUDER_MIDDLE_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_upper(EXTRUDER_UPPER_PORT, pros::v5::MotorGears::green);

    bool driverReverse = false;

    while (true) {
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
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                extruder_lift.move(127);
                extruder_lower.move(127);
                extruder_middle.move(-127);
                extruder_upper.move(0);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                extruder_lift.move(127);
                extruder_lower.move(127);
                extruder_middle.move(127);
                extruder_upper.move(-127);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                extruder_lift.move(127);
                extruder_lower.move(127);
                extruder_middle.move(127);
                extruder_upper.move(127);
            } else {
                extruder_lift.move(0);
                extruder_lower.move(0);
                extruder_middle.move(0);
                extruder_upper.move(0);
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
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                extruder_lift.move(-127);
                extruder_lower.move(-127);
                extruder_middle.move(127);
                extruder_upper.move(0);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                extruder_lift.move(-127);
                extruder_lower.move(-127);
                extruder_middle.move(-127);
                extruder_upper.move(127);
            } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                extruder_lift.move(-127);
                extruder_lower.move(-127);
                extruder_middle.move(-127);
                extruder_upper.move(-127);
            } else {
                extruder_lift.move(0);
                extruder_lower.move(0);
                extruder_middle.move(0);
                extruder_upper.move(0);
            }
        }

        pros::delay(2);
    }
}

float distToRevos(float dist) {
    float wheelRadius = 2.0625;
    float slipCorrection = 1.075;
    return (dist/(2*PI*wheelRadius))*slipCorrection;
}

float angleToRevos(float angleDeg) {
    float wheelbase = 9.0;
    float wheelRadius = 2.0625;
    float theta = angleDeg*PI/180;
    float slipCorrection = 1.075;
    float revos = (theta*wheelbase)/(4*PI*wheelRadius);
    return revos*slipCorrection;
}

void autonomous() {
    pros::Motor left_wheels(LEFT_WHEELS_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::Motor right_wheels(RIGHT_WHEELS_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::Motor feeder(FEEDER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_lift(EXTRUDER_LIFT_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_lower(EXTRUDER_LOWER_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_middle(EXTRUDER_MIDDLE_PORT, pros::v5::MotorGears::green);
    pros::Motor extruder_upper(EXTRUDER_UPPER_PORT, pros::v5::MotorGears::green);
/*
    left_wheels.move_relative(distToRevos(8), 127);
    right_wheels.move_relative(distToRevos(8), 127);

    pros::delay(2000);

    left_wheels.move_relative(angleToRevos(360), 127);
    right_wheels.move_relative(angleToRevos(360)*-1, 127);

    pros::delay(3000);

    left_wheels.move_relative(distToRevos(6), 127);
    right_wheels.move_relative(distToRevos(6), 127);
*/
}
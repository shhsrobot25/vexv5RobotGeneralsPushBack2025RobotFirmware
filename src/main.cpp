#include "main.h"

#define LEFT_WHEELS_PORT 15
#define RIGHT_WHEELS_PORT -13
#define FEEDER_A_RIGHT_PORT 12
#define FEEDER_A_LEFT_PORT -1
#define FEEDER_B_RIGHT_PORT -11
#define FEEDER_B_LEFT_PORT 14
#define CONVEYER_PORT -8
#define RAMP_PORT -9

void opcontrol() {
    pros::Controller master(CONTROLLER_MASTER);
    pros::Controller partner(CONTROLLER_PARTNER);

    pros::Motor left_wheels(LEFT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::Motor right_wheels(RIGHT_WHEELS_PORT, pros::v5::MotorGears::green);
    pros::MotorGroup feeder_a({FEEDER_A_RIGHT_PORT, FEEDER_A_LEFT_PORT}, pros::v5::MotorGears::blue);
    pros::MotorGroup feeder_b({FEEDER_B_RIGHT_PORT, FEEDER_B_LEFT_PORT}, pros::v5::MotorGears::green);
    pros::Motor conveyer(CONVEYER_PORT, pros::v5::MotorGears::green);
    pros::Motor ramp(RAMP_PORT, pros::v5::MotorGears::red);

    ramp.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

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

        // partner controls
        if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            ramp.move(127);
        } else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            ramp.move(-32);
        } else {
            ramp.brake();
        }

        // reversable partner controls
        if (!partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
                feeder_a.move(64);
            } else {
                feeder_a.move(0);
            }
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
                feeder_b.move(64);
            } else {
                feeder_b.move(0);
            }
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
                conveyer.move(24);
            } else {
                conveyer.move(0);
            }
        } else {
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
                feeder_a.move(-64);
            } else {
                feeder_a.move(0);
            }
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
                feeder_b.move(-64);
            } else {
                feeder_b.move(0);
            }
            if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
                conveyer.move(-24);
            } else {
                conveyer.move(0);
            }
        }

        pros::delay(2);
    }
}

void autonomous() {
    pros::Motor left_wheels(LEFT_WHEELS_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::Motor right_wheels(RIGHT_WHEELS_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::MotorGroup feeder_a({FEEDER_A_RIGHT_PORT, FEEDER_A_LEFT_PORT}, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::MotorGroup feeder_b({FEEDER_B_RIGHT_PORT, FEEDER_B_LEFT_PORT}, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::Motor conveyer(CONVEYER_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);
    pros::Motor ramp(RAMP_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::rotations);

    ramp.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
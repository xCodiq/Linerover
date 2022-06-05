//
// Created by elmar on 19/05/2022.
//

#include "MotorController.h"

MotorController::MotorController() {
    // Set all the pins required for the motor to function
    int ports[] = {
            Pins::MOTOR_ACTIVATION_PORT,
            Pins::MOTOR_COUNTER_CLOCKWISE_PORT,
            Pins::MOTOR_CLOCKWISE_PORT,
            Pins::MOTOR_SPEED_CONTROL_PORT
    };

    for (const auto &port: ports) pinMode(port, OUTPUT);
}

MotorController::~MotorController() {
    delete MotorController::instance;
}

MotorController &MotorController::configure() {
    return *(instance = new MotorController{});
}

MotorController &MotorController::get() {
    return *instance;
}

void MotorController::adjustSpeed(int speed) {
    analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, speed);
}

void MotorController::throttle(const State &state) {
    // Check if the state is STARTING, if true, start the motor
    if (state == State::STARTING) {
        digitalWrite(Pins::MOTOR_ACTIVATION_PORT, HIGH);
        return;
    }

    // Get the speed for the specified state
    int motorSpeed = MotorSpeed::getSpeed(state);

    // Adjust the (counter) clockwise pins and give a HIGH signal to the activation port
    digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, LOW);
    digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, HIGH);
    digitalWrite(Pins::MOTOR_ACTIVATION_PORT, HIGH);

    // Analog write the motor speed to the motor speed control port
    adjustSpeed(motorSpeed);
}

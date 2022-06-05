//
// Created by elmar on 25/05/2022.
//

#include "SurpassSlopeScript.h"

State SurpassSlopeScript::run() {
    // Get an instance of all the controllers and handlers you need
    auto &servoController = ServoController::get();
    auto &motorController = MotorController::get();
    auto &infraredController = InfraredController::get();
    auto &scriptHandler = ScriptHandler::get();

    // Check if it's the initial run, if true, reset the time field to the current millis
    if (this->m_time == 0) this->m_time = millis();

    switch (this->m_phase) {
        case 1: { // PHASE 1: Drive backwards to make some room for full acceleration
            if (millis() - this->m_time < 150) { // 0.150 seconds
                // Set the motor to counterclockwise
                digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, HIGH);
                digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, LOW);

                analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, 255);
                digitalWrite(Pins::MOTOR_ACTIVATION_PORT, HIGH);
            } else {
                this->m_time = millis();
                this->m_phase = 2; // Switch to phase 2
            }

            return State::ACCELERATE;
        }
        case 2: { // PHASE 2: Adjust the speed for half a second to make sure it can make it over the slope
            if (millis() - this->m_time < 2000) { // 2 seconds
                // Make the Linerover have $ACCELERATE PWM
                digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, LOW);
                digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, HIGH);

                motorController.adjustSpeed(MotorSpeed::getSpeed(State::ACCELERATE));
            } else {
                this->m_time = millis();
                this->m_phase = 3; // Switch to phase 3
            }

            return State::ACCELERATE;
        }
        case 3: { // PHASE 3: Adjust the speed to 0 for half a second to slow it down when it goes down the slope
            if (millis() - this->m_time < 500) { // 0.5 seconds
                // Make the Linerover have 0 PWM
                motorController.adjustSpeed(0);
            } else {
                this->m_time = millis();
                this->m_phase = 4; // Switch to phase 4
            }

            return State::ACCELERATE;
        }
        case 4: // PHASE 4: Set the current state to NORMAL, and reset the script variables
        default: {
            this->m_time = 0;
            this->m_phase = 1; // Reset script to phase 1
            return State::NORMAL;
        }
    }
}

//
// Created by elmar on 23/05/2022.
//

#include "AvoidObstacleScript.h"

State AvoidObstacleScript::run() {
    // Get an instance of all the controllers and handlers you need
    auto &servoController = ServoController::get();
    auto &motorController = MotorController::get();
    auto &infraredController = InfraredController::get();

    // Check if it's the initial run, if true, reset the m_time field to the current millis
    if (this->m_time == 0) this->m_time = millis();

    switch (this->m_phase) {
        case 1: // PHASE 1: Steer to the right, to make room for a turn
            if (millis() - this->m_time < 1500) { // 1.5 seconds
                // Make the Linerover steer to the right
                servoController.changeDirection(Direction::RIGHT);
            } else {
                this->m_time = millis();
                this->m_phase = 2; // Switch to phase 2
            }

            return State::OBSTACLE;

        case 2: // PHASE 2: Steer to the left, so the it'll turn back to the white line
            if (millis() - this->m_time < 500) { // 0.5 seconds
                servoController.changeDirection(Direction::LEFT);
            } else {
                this->m_time = millis();
                this->m_phase = 3; // Switch to phase 3
            }

            return State::OBSTACLE;

        case 3: // PHASE 3: Check if the 4th infrared sensor picks up a line, if true, set state to NORMAL
        default:
            return infraredController.readSensor(Pins::INFRARED_SENSOR_4_PORT) ? State::NORMAL : State::OBSTACLE;

    }
}
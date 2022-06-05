//
// Created by elmar on 23/05/2022.
//

#include "AvoidObstacleScript.h"

State AvoidObstacleScript::run() {
    // Get an instance of all the controllers and handlers you need
    auto &servoController = ServoController::get();
    auto &infraredController = InfraredController::get();
    auto &scriptHandler = ScriptHandler::get();

    // Check if it's the initial run, if true, reset the time field to the current millis
    if (this->m_time == 0) this->m_time = millis();

    switch (this->m_phase) {
        case 1: { // PHASE 1: Steer to the right, to make room for a turn
            if (millis() - this->m_time < 780) {
                // Make the Linerover steer to the right
                servoController.changeDirection(Direction::RIGHT_OBSTACLE);
            } else {
                this->m_time = millis();
                this->m_phase = 2; // Switch to phase 2
            }

            return State::OBSTACLE;
        }
        case 2: { // PHASE 2: Steer to the left, so the it'll turn back to the white line
            if (millis() - this->m_time < 100) {
                // Make the Linerover steer to the left
                servoController.changeDirection(Direction::LEFT_OBSTACLE);
            } else {
                this->m_time = millis();
                this->m_phase = 3; // Switch to phase 3
            }

            return State::OBSTACLE;
        }
        case 3: // PHASE 3: Check if the 3rd or 4th infrared sensor picks up a line, if true, set state to NORMAL
        default: {
            if (infraredController.readSensor(Pins::INFRARED_SENSOR_3_PORT) ||
                infraredController.readSensor(Pins::INFRARED_SENSOR_4_PORT)) {
                // Set the passed obstacle boolean to true for next iterations
                scriptHandler.passedObstacle() = true;

                this->m_time = 0;
                this->m_phase = 1; // Reset script to phase 1

                return State::NORMAL;
            }

            return State::OBSTACLE;
        }
    }
}
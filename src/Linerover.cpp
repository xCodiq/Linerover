//
// Created by elmar on 06/04/2022.
// GROUP NUMBER: 4

#include "Linerover.h"

void Linerover::startEngine() {
    Logger::info("Starting engine...");

    // Get the state handler, and set the starting state to NORMAL
    auto &stateHandler = StateHandler::get();
    stateHandler.currentState() = State::STARTING;

    // Configure the ServoController, and face forward
    auto &servoController = ServoController::configure(Pins::SERVO_PORT);
    servoController.changeDirection(Direction::FORWARD);

    // Configure the EchoController
    auto &echoController = EchoController::configure();

    // Configure the InfraredController
    auto &infraredController = InfraredController::configure();

    // Configure the MotorController
    auto &motorController = MotorController::configure();
    motorController.throttle(State::STARTING);

    // Configure the ScriptHandler and enable the scripts
    auto &scriptHandler = ScriptHandler::configure();

//    auto avoidObstacleScript = AvoidObstacleScript{};
//    scriptHandler.enableScript(&avoidObstacleScript);

//    auto surpassSlopeScript = SurpassSlopeScript();
//    scriptHandler.enableScript(&surpassSlopeScript);

    // Change the state to normal for the Linerover to know it's ready for driving
    stateHandler.currentState() = State::NORMAL;
}

unsigned long m_time = 0;
int m_phase = 1;

bool Linerover::drive() {
    // Get the instances of all the handlers and controllers we need to let the Linerover drive
    auto &stateHandler = StateHandler::get();
    auto &servoController = ServoController::get();
    auto &echoController = EchoController::get();
    auto &infraredController = InfraredController::get();
    auto &motorController = MotorController::get();
    auto &scriptHandler = ScriptHandler::get();

    // Get the current sensor state of the Linerover
    State currentState = stateHandler.currentState();

    // Switch the current state to perform actions accordingly
    switch (currentState) {
        case NORMAL: {
            // Use the motor controller to throttle the motor, speed is set for each state
            motorController.throttle(currentState);

            // Check alignment the steering should point to
            Direction checkedDirection = infraredController.checkAlignment();

            // Check if the checked direction is FINISH, if so, go to a stopping state!
            if (checkedDirection == Direction::FINISH) {
                stateHandler.currentState() = State::STOPPING;
                return true;
            }

            // Change the servo direction to the newly checked direction. The servo direction will not be changed
            // if the previous direction is equal to that newly checked direction.
            if (servoController.changeDirection(checkedDirection)) return true;

            // Check if there is an obstacle of any type nearby
//            ObstacleType obstacleTypeNearby = echoController.isObstacleNearby();
//            if (obstacleTypeNearby != ObstacleType::NONE) {
//                State newState = (obstacleTypeNearby == ObstacleType::SLOPE) ? State::ACCELERATE : State::OBSTACLE;
//                stateHandler.currentState() = newState;
//                Logger::info("OBSTACLE state!");
//                return true;
//            }

            return true;
        }
        case ACCELERATE: {
            // Get the SURPASS_SLOPE script from the script handler
            Script *script = scriptHandler.getScript(ScriptTarget::SURPASS_SLOPE);

            // Check if the script is pointing to a nullptr, that means it is not enabled properly in startEngine
            if (script == nullptr) {
                stateHandler.currentState() = State::NORMAL;
                return true;
            }

//            delay(500);
            stateHandler.currentState() = script->run();
            return true;
        }
        case OBSTACLE: {
            // Use the motor controller to throttle the motor, speed is set for each state
            motorController.throttle(currentState);

//            // Get the AVOID_OBSTACLE script from the script handler
//            Script *script = scriptHandler.getScript(ScriptTarget::AVOID_OBSTACLE);
//
//            // Check if the script is pointing to a nullptr, that means it is not enabled properly in startEngine
//            if (script == nullptr) {
//                stateHandler.currentState() = State::NORMAL;
//                return true;
//            }
//
////            delay(500);
//            stateHandler.currentState() = script->run();
            // Check if it's the initial run, if true, reset the m_time field to the current millis
            if (m_time == 0) m_time = millis();

            switch (m_phase) {
                case 1: {// PHASE 1: Steer to the right, to make room for a turn
                    if (millis() - m_time < 2500) { // 1.5 seconds
                        // Make the Linerover steer to the right
                        servoController.changeDirection(Direction::RIGHT);
                        Logger::info("PHASE 1");
                    } else {
                        m_time = millis();
                        m_phase = 2; // Switch to phase 2
                        Logger::info("Switched to phase 2");
                    }

                    return true;
//                    stateHandler.currentState() = State::OBSTACLE;
                }
                case 2: {// PHASE 2: Steer to the left, so the it'll turn back to the white line
                    if (millis() - m_time < 2000) { // 0.5 seconds
                        servoController.changeDirection(Direction::LEFT);
                        Logger::info("PHASE 2");
                    } else {
                        m_time = millis();
                        m_phase = 3; // Switch to phase 3
                        Logger::info("Switched to phase 3");
                    }

                    stateHandler.currentState() = State::OBSTACLE;
                    return true;
                }
                case 3: // PHASE 3: Check if the 4th infrared sensor picks up a line, if true, set state to NORMAL
                default: {
                    Logger::info("PHASE 3");
                    if (infraredController.readSensor(Pins::INFRARED_SENSOR_4_PORT)) {
                        stateHandler.currentState() = State::NORMAL;
                        m_time = 0;
                        m_phase = 1;
                        Logger::info("NORMAL state!");
                    } else {
                        stateHandler.currentState() = State::OBSTACLE;
                    }
                    return true;
                }
            }
            return true;
        }
        case STOPPING: {
            Logger::info("STOPPINGG!!!!!");
            servoController.changeDirection(Direction::FORWARD);

            digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, HIGH);
            digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, LOW);
            analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, 255);
            delay(300);
            analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, 0);
            delay(2000);
            digitalWrite(Pins::MOTOR_ACTIVATION_PORT, LOW);

//            motorController.throttle(State::STOPPING);
//            delay(500);
//            motorController.adjustSpeed(0);
            return false;
        }
        case STARTING:
            return true;
        default:
            return false;
    }
}


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

    auto avoidObstacleScript = AvoidObstacleScript();
    scriptHandler.enableScript(&avoidObstacleScript);

    auto surpassSlopeScript = SurpassSlopeScript();
    scriptHandler.enableScript(&surpassSlopeScript);

    // Change the state to normal for the Linerover to know it's ready for driving
    stateHandler.currentState() = State::NORMAL;
}

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

    // Use the motor controller to throttle the motor, speed is set for each state
    motorController.throttle(currentState);

    // Switch the current state to perform actions accordingly
    switch (currentState) {
        case NORMAL: {
            // Check the alignment the steering should point to
            Direction checkedDirection = infraredController.checkAlignment();

            // Change the servo direction to the newly checked direction. The servo direction will not be changed
            // if the previous direction is equal to that newly checked direction.
            if (servoController.changeDirection(checkedDirection)) return true;

            // Check if there is an obstacle of any type nearby
            ObstacleType obstacleTypeNearby = echoController.isObstacleNearby();
            if (obstacleTypeNearby != ObstacleType::NONE) {
                State newState = (obstacleTypeNearby == ObstacleType::SLOPE) ? State::ACCELERATE : State::OBSTACLE;
                stateHandler.currentState() = newState;
            }

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

            delay(500);
            stateHandler.currentState() = script->run();
            return true;
        }
        case OBSTACLE: {
            // Get the AVOID_OBSTACLE script from the script handler
            Script *script = scriptHandler.getScript(ScriptTarget::AVOID_OBSTACLE);

            // Check if the script is pointing to a nullptr, that means it is not enabled properly in startEngine
            if (script == nullptr) {
                stateHandler.currentState() = State::NORMAL;
                return true;
            }

            delay(500);
            stateHandler.currentState() = script->run();
            return true;
        }
        case STARTING:
            return true;
        default:
            return false;
    }
}


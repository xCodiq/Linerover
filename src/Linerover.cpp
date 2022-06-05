//
// Created by elmar on 06/04/2022.
// GROUP NUMBER: 4

#include "Linerover.h"

void Linerover::startEngine() {
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
            ObstacleType obstacleTypeNearby = echoController.isObstacleNearby();
            if (obstacleTypeNearby != ObstacleType::NONE) {
                State newState = (obstacleTypeNearby == ObstacleType::SLOPE) ? State::ACCELERATE : State::OBSTACLE;

                // Change the state to either OBSTACLE or ACCELERATE
                stateHandler.currentState() = newState;
                return true;
            }

            // Current cycle was successful, continue to the next
            return true;
        }
        case ACCELERATE: {
            // Get the avoid obstacle script, and run it
            SurpassSlopeScript surpassSlopeScript = scriptHandler.getSurpassSlopeScript();
            return (stateHandler.currentState() = surpassSlopeScript.run()) != State::STARTING;
        }
        case OBSTACLE: {
            // Use the motor controller to throttle the motor, speed is set for each state
            motorController.throttle(currentState);

            // Get the avoid obstacle script, and run it
            AvoidObstacleScript avoidObstacleScript = scriptHandler.getAvoidObstacleScript();
            return (stateHandler.currentState() = avoidObstacleScript.run()) != State::STARTING;
        }
        case STOPPING: {
            // Change the direction to forward
            servoController.changeDirection(Direction::FORWARD);

            // Use the motor controller to throttle the motor, speed is set for each state
            motorController.throttle(currentState);

            // Return false so the Linerover stops working, unless you reset/reboot
            return false;
        }
        case STARTING:
            return true;
        default:
            return false;
    }
}
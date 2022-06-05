//
// Created by elmar on 06/04/2022.
// GROUP NUMBER: 4

#include "Linerover.h"

void Linerover::startEngine() {
//    Logger::info("Starting engine...");

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
                if (newState == State::ACCELERATE) delay(1000);

                // Change the state to either OBSTACLE or ACCELERATE
                stateHandler.currentState() = newState;
                return true;
            }

            // Current cycle was successful, continue to the next
            return true;
        }
        case ACCELERATE: {
            // Check if it's the initial run, if true, reset the time field to the current millis
            if (scriptHandler.slopeTime() == 0) scriptHandler.slopeTime() = millis();

            switch (scriptHandler.slopePhase()) {
                case 1: {
                    if (millis() - scriptHandler.slopeTime() < 150) { // 0.5 seconds
                        // Make the Linerover have $ACCELERATE PWM

                        // Drive backwards for half a second
                        digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, HIGH);
                        digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, LOW);

                        analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, 255);
                        digitalWrite(Pins::MOTOR_ACTIVATION_PORT, HIGH);
                    } else {
                        scriptHandler.slopeTime() = millis();
                        scriptHandler.slopePhase() = 2; // Switch to phase 2
                    }

                    return true;
                }
                case 2: { // PHASE 1: Adjust the speed for half a second to make sure it can make it over the slope
                    if (millis() - scriptHandler.slopeTime() < 2000) { // 0.5 seconds
                        // Make the Linerover have $ACCELERATE PWM
                        digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, LOW);
                        digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, HIGH);
                        motorController.adjustSpeed(MotorSpeed::getSpeed(State::ACCELERATE));
                    } else {
                        scriptHandler.slopeTime() = millis();
                        scriptHandler.slopePhase() = 3; // Switch to phase 2
                    }

                    return true;
                }
                case 3: { // PHASE 2: Adjust the speed to 0 for half a second to slow it down when it goes down the slope
                    if (millis() - scriptHandler.slopeTime() < 500) { // 0.5 seconds
                        // Make the Linerover have 0 PWM
                        motorController.adjustSpeed(0);
                    } else {
                        scriptHandler.slopeTime() = millis();
                        scriptHandler.slopePhase() = 4; // Switch to phase 3
                    }

                    return true;
                }
                case 4: // PHASE 3: Set the current state to NORMAL, and reset the script variables
                default: {
                    stateHandler.currentState() = State::NORMAL;
                    scriptHandler.slopeTime() = 0;
                    scriptHandler.slopePhase() = 1; // Reset script to phase 1
                    return true;
                }
            }
        }
        case OBSTACLE: {
            // Use the motor controller to throttle the motor, speed is set for each state
            motorController.throttle(currentState);

            // Check if it's the initial run, if true, reset the time field to the current millis
            if (scriptHandler.obstacleTime() == 0) scriptHandler.obstacleTime() = millis();

            switch (scriptHandler.obstaclePhase()) {
                case 1: { // PHASE 1: Steer to the right, to make room for a turn
                    if (millis() - scriptHandler.obstacleTime() < 780) {
                        // Make the Linerover steer to the right
                        servoController.changeDirection(Direction::RIGHT_OBSTACLE);
                    } else {
                        scriptHandler.obstacleTime() = millis();
                        scriptHandler.obstaclePhase() = 2; // Switch to phase 2
                    }

                    return true;
                }
                case 2: { // PHASE 2: Steer to the left, so the it'll turn back to the white line
                    if (millis() - scriptHandler.obstacleTime() < 100) {
                        // Make the Linerover steer to the left
                        servoController.changeDirection(Direction::LEFT_OBSTACLE);
                    } else {
                        scriptHandler.obstacleTime() = millis();
                        scriptHandler.obstaclePhase() = 3; // Switch to phase 3
                    }

                    return true;
                }
                case 3: // PHASE 3: Check if the 3rd or 4th infrared sensor picks up a line, if true, set state to NORMAL
                default: {
                    if (infraredController.readSensor(Pins::INFRARED_SENSOR_3_PORT) ||
                        infraredController.readSensor(Pins::INFRARED_SENSOR_4_PORT)) {
                        stateHandler.currentState() = State::NORMAL;

                        // Set the passed obstacle boolean to true for next iterations
                        scriptHandler.passedObstacle() = true;

                        scriptHandler.obstacleTime() = 0;
                        scriptHandler.obstaclePhase() = 1; // Reset script to phase 1
                    } else stateHandler.currentState() = State::OBSTACLE;
                    return true;
                }
            }
        }
        case STOPPING: {
            // Change the direction to forward
            servoController.changeDirection(Direction::FORWARD);

            // Drive backwards for half a second
            digitalWrite(Pins::MOTOR_COUNTER_CLOCKWISE_PORT, HIGH);
            digitalWrite(Pins::MOTOR_CLOCKWISE_PORT, LOW);
            analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, 255);
            delay(620);

            // Set the speed to 0, and disable the motor after 1 second
            analogWrite(Pins::MOTOR_SPEED_CONTROL_PORT, 0);
            delay(1000);
            digitalWrite(Pins::MOTOR_ACTIVATION_PORT, LOW);

            // Return false so the Linerover stops working, unless you reset/reboot
            return false;
        }
        case STARTING:
            return true;
        default:
            return false;
    }
}
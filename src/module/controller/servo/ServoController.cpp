//
// Created by elmar on 06/04/2022.
//

#include "ServoController.h"

ServoController::ServoController(int servoPort) : m_servoPort(servoPort), m_servo({}) {
    this->m_servo.attach(this->m_servoPort);
}

ServoController::~ServoController() {
    delete ServoController::instance;
}

ServoController &ServoController::configure(int port) {
    return *(instance = new ServoController{port});
}

ServoController &ServoController::get() {
    return *instance;
}

void ServoController::update() {
    this->m_servo.write(this->m_currentDirection);
}

bool ServoController::changeDirection(const Direction &direction) {
    // Check if the direction is UNKNOWN or the direction is equal to the previous direction the servo steered to
    if (direction == Direction::UNKNOWN || direction == this->m_currentDirection) return false;

    // Change the previous direction to the current one, change the current one to the given direction and update servo
    this->m_currentDirection = direction;
    this->update();

    // Return true, saying the change of direction was successful
    return true;
}


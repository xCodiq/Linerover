//
// Created by elmar on 15/05/2022.
//

#include "InfraredController.h"

InfraredController::InfraredController() {
    // Set all the pin modes of the infrared ports
    int ports[] = {
            Pins::INFRARED_SENSOR_1_PORT,
            Pins::INFRARED_SENSOR_2_PORT,
            Pins::INFRARED_SENSOR_3_PORT,
            Pins::INFRARED_SENSOR_4_PORT,
            Pins::INFRARED_SENSOR_5_PORT
    };

    for (const auto &port: ports) pinMode(port, INPUT);

    Logger::info("InfraredController has been enabled!");
}

InfraredController::~InfraredController() {
    delete InfraredController::instance;
}

InfraredController &InfraredController::configure() {
    if (instance == nullptr) return *(instance = new InfraredController{});

    Logger::error("You are not allowed to configure a InfraredController twice!");
}

InfraredController &InfraredController::get() {
    if (instance != nullptr) return *instance;

    Logger::error("You haven't configured a InfraredController yet!");
}

bool InfraredController::readSensor(int sensorPort) {
    return digitalRead(sensorPort) == 0;
}

Direction InfraredController::checkAlignment() {
    if (readSensor(Pins::INFRARED_SENSOR_1_PORT)) return Direction::SHARP_LEFT;
    else if (readSensor(Pins::INFRARED_SENSOR_2_PORT)) return Direction::LEFT;
    else if (readSensor(Pins::INFRARED_SENSOR_3_PORT)) return Direction::FORWARD;
    else if (readSensor(Pins::INFRARED_SENSOR_4_PORT)) return Direction::RIGHT;
    else if (readSensor(Pins::INFRARED_SENSOR_5_PORT)) return Direction::SHARP_RIGHT;
    else return Direction::UNKNOWN;
}

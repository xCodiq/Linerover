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
}

InfraredController::~InfraredController() {
    delete InfraredController::instance;
}

InfraredController &InfraredController::configure() {
    return *(instance = new InfraredController{});
}

InfraredController &InfraredController::get() {
    return *instance;
}

bool InfraredController::readSensor(int sensorPort) {
    return digitalRead(sensorPort) == 0;
}

Direction InfraredController::checkAlignment() {
    bool readSensorOne = readSensor(Pins::INFRARED_SENSOR_1_PORT);
    bool readSensorTwo = readSensor(Pins::INFRARED_SENSOR_2_PORT);
    bool readSensorThree = readSensor(Pins::INFRARED_SENSOR_3_PORT);
    bool readSensorFour = readSensor(Pins::INFRARED_SENSOR_4_PORT);
    bool readSensorFive = readSensor(Pins::INFRARED_SENSOR_5_PORT);

    if ((readSensorOne && readSensorTwo && readSensorThree && readSensorFour && readSensorFive))
        return Direction::FINISH;

    if (readSensorOne) return Direction::SHARP_LEFT;
    if (readSensorTwo) return Direction::LEFT;
    if (readSensorThree) return Direction::FORWARD;
    if (readSensorFour) return Direction::RIGHT;
    if (readSensorFive) return Direction::SHARP_RIGHT;

    return Direction::UNKNOWN;
}

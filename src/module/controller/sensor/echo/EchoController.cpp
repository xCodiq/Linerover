//
// Created by elmar on 15/05/2022.
//

#include "EchoController.h"
#include "module/script/handler/ScriptHandler.h"

EchoController::EchoController() {
    // Set the pin modes of the echo data and the echo trigger port
    pinMode(Pins::ECHO_TRIGGER_PORT, OUTPUT);
    pinMode(Pins::ECHO_DATA_PORT, INPUT);

    pinMode(Pins::ECHO_TRIGGER2_PORT, OUTPUT);
    pinMode(Pins::ECHO_DATA2_PORT, INPUT);

    Logger::info("EchoController has been enabled!");
}

EchoController::~EchoController() {
    delete EchoController::instance;
}

EchoController &EchoController::configure() {
    if (instance == nullptr) return *(instance = new EchoController{});

    Logger::error("You are not allowed to configure a EchoController twice!");
}

EchoController &EchoController::get() {
    if (instance != nullptr) return *instance;

    Logger::error("You haven't configured a EchoController yet!");
}

unsigned int EchoController::echo(const Location &echoLocation) {
    // Determine the ports of the specified echo sensor location
    EchoSensorPorts ports = Echo::getPorts(echoLocation);

    // Clear the trigger pin condition
    digitalWrite(ports.triggerPort, LOW);
    delayMicroseconds(2);

    // Sets the trigger pin to HIGH for 10us
    digitalWrite(ports.triggerPort, HIGH);
    delayMicroseconds(10);
    digitalWrite(ports.triggerPort, LOW);

    // Read the echo data pin, returns the sound wave travel time in microseconds (us)
    unsigned long duration = pulseIn(ports.dataPort, HIGH);

    // Calculate the distance
    int distance = duration * SPEED_OF_SOUND / 2;
    return (distance > DISTANCE_LOWER_BOUND && distance < DISTANCE_UPPER_BOUND) ? distance : 0;
}

ObstacleType EchoController::isObstacleNearby() {
    // Read the lower echo sensor
    unsigned int echoLower = echo(Location::LOWER);

    // Get an instance of the script handler for the echo controller to use
    auto &scriptHandler = ScriptHandler::get();

    // Check if the obstacle is not passed yet, and the echo lower sees an object from far
    if (!scriptHandler.passedObstacle() && (echoLower >= 30 && echoLower <= 40)) return ObstacleType::BARRIER;

    // Check if the obstacle IS passed, and the echo lower sees an object from close
    if (scriptHandler.passedObstacle() && (echoLower >= 5 && echoLower <= 8)) return ObstacleType::SLOPE;

    // There might be an object, but not relevant for the Linerover to respond to
    return ObstacleType::NONE;
}


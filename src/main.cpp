#include "Linerover.h"

bool RUNNING = false;
bool LOGGING = true;

void setup() {
    // Configure the linerover logger
    if (LOGGING) Logger::configure(Pins::SERIAL_BAUD);

    // Linerover#startEngine() is used to enable the car, initialize all the controllers,
    // and make sure everything is ready before driving/looping
    Linerover::startEngine();

    // Set the global boolean variable to true for the loop function to start working
    RUNNING = true;
}

void loop() {
    // Having a while loop will give us the ability to stop looping
    // whenever we want, without killing/stopping the entire program.
    while (RUNNING) {
        if (!(RUNNING = Linerover::drive())) break;
    }
}
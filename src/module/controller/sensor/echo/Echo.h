//
// Created by elmar on 17/05/2022.
//

#ifndef LINEROVER_ECHO_H
#define LINEROVER_ECHO_H

#include "module/pin/Pins.h"

struct EchoSensorPorts {
    // The data pin port of the echo sensor pair
    int dataPort;

    // The trigger pin port of the echo sensor pair
    int triggerPort;
};

enum ObstacleType {
    // Enumeration for an unknown obstacle, also known as nothing ;)
    NONE,

    // Enumeration for a slope obstacle
    SLOPE,

    // Enumeration for a barrier obstacle
    BARRIER
};

enum Location {
    // The upper location of an echo sensor
    UPPER, // unused

    // The lower location of an echo sensor
    LOWER
};

class Echo {
public:

    /**
     * Get the echo sensor ports of a specific echo sensor location
     *
     * @param sensorLocation the echo sensor location
     * @return the echo sensor ports of the specific echo sensor location
     * @see EchoSensorPorts
     */
    static EchoSensorPorts getPorts(const Location &sensorLocation);
};


#endif //LINEROVER_ECHO_H

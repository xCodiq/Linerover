//
// Created by elmar on 17/05/2022.
//

#include "Echo.h"

EchoSensorPorts Echo::getPorts(const Location &sensorLocation) {
    switch (sensorLocation) {
        case LOWER:
            return {Pins::ECHO_DATA_PORT, Pins::ECHO_TRIGGER_PORT};
        case UPPER:
            return {Pins::ECHO_DATA2_PORT, Pins::ECHO_TRIGGER2_PORT};
        default:
            return {-1, -1};
    }
}

//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_CONTROLLER_H
#define LINEROVER_CONTROLLER_H

#include <Arduino.h>
#include <Vector.h>

#include "module/state/State.h"
#include "module/logger/Logger.h"
#include "module/pin/Pins.h"

/**
 * Every module of the Linerover will have it's own Controller
 * that does it's own purpose. There fore, the modules are nicely
 * separated into classes/headers for more flexibility and efficiency.
 */
class Controller {
};

#endif //LINEROVER_CONTROLLER_H

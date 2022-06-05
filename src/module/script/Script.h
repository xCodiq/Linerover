//
// Created by elmar on 23/05/2022.
//

#ifndef LINEROVER_SCRIPT_H
#define LINEROVER_SCRIPT_H

#include "../controller/Controller.h"
#include "../controller/motor/MotorController.h"
#include "../controller/servo/ServoController.h"
#include "../controller/sensor/echo/EchoController.h"
#include "../controller/sensor/infrared/InfraredController.h"
#include "handler/ScriptHandler.h"

enum ScriptTarget {
    // Script Target for avoiding the obstacle
    AVOID_OBSTACLE,

    // Script Target for surpassing the big slope
    SURPASS_SLOPE
};

class Script {
public:
    /**
     * This function should be called to run the Script.
     *
     * @return the new state for the next cycle
     */
    virtual State run() = 0;

    /**
     * The script target enumeration flag of the script itself
     *
     * @return the script target enumeration flag
     */
    virtual ScriptTarget target() = 0;
};

#endif //LINEROVER_SCRIPT_H

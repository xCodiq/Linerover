//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_LINEROVER_H
#define LINEROVER_LINEROVER_H

#include <Arduino.h>

#include "module/logger/Logger.h"
#include "module/pin/Pins.h"

#include "module/state/StateHandler.h"
#include "module/controller/servo/ServoController.h"
#include "module/controller/sensor/echo/EchoController.h"
#include "module/controller/sensor/infrared/InfraredController.h"
#include "module/controller/motor/MotorController.h"
#include "module/script/handler/ScriptHandler.h"

namespace Linerover {

    /**
     * This function is used to start the Linerover robot. This is very
     * similar to the setup() function the Arduino framework uses
     */
    void startEngine();

    /**
     * This function will be used as our loop to act as a thread function.
     * It will be called very very often. This function is very similar
     * to the loop() function the Arduino framework uses
     *
     * @return TRUE if the cycle was successful and the Linerover can
     * move to the next cycle, false if something went wrong
     */
    bool drive();

}


#endif //LINEROVER_LINEROVER_H

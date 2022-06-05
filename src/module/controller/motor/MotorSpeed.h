//
// Created by elmar on 20/05/2022.
//

#ifndef LINEROVER_MOTORSPEED_H
#define LINEROVER_MOTORSPEED_H

#include "../../state/State.h"

class MotorSpeed {
public:

    /**
     * Get the motor speed of a specific State
     *
     * @param state the State to get it's corresponding speed of
     * @return the motor speed of the specific State
     */
    static int getSpeed(const State &state) {
        switch (state) {
            case NORMAL:
                return 70;
            case ACCELERATE:
                return 210;
            case OBSTACLE:
                return 64;
            case STARTING:
            case STOPPING:
            default:
                return 0;
        }
    }
};


#endif //LINEROVER_MOTORSPEED_H

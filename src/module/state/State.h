//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_STATE_H
#define LINEROVER_STATE_H


enum State {
    // Starting state for the Linerover
    STARTING,

    // Just following the line, default state
    NORMAL,

    // Slope detected, different sensor behaviour
    ACCELERATE,

    // Obstacle detected, drive a circle around an object
    OBSTACLE
};


#endif //LINEROVER_STATE_H

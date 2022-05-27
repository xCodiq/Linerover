//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_STATEHANDLER_H
#define LINEROVER_STATEHANDLER_H

#include "State.h"

class StateHandler {
private:
    // The instance pointer of the StateHandler
    static inline StateHandler *instance = nullptr;

    // The current state of the Linerover
    State m_currentState = State::NORMAL;

    StateHandler() = default;

    ~StateHandler();

public:
    StateHandler(StateHandler &) = delete;

    StateHandler &operator=(StateHandler &) = delete;

    /**
     * Get the only instance of the StateHandler for the Linerover
     *
     * @return the instance of the StateHandler
     */
    static StateHandler &get();

    /**
     * Get/Set the current state of the Linerover
     *
     * @return the current state of the Linerover
     */
    State &currentState();
};


#endif //LINEROVER_STATEHANDLER_H

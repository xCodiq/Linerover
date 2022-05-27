//
// Created by elmar on 06/04/2022.
//

#include "StateHandler.h"

StateHandler::~StateHandler() {
    delete StateHandler::instance;
}

StateHandler &StateHandler::get() {
    if (instance != nullptr) return *instance;

    return *(instance = new StateHandler());
}

State &StateHandler::currentState() {
    return this->m_currentState;
}

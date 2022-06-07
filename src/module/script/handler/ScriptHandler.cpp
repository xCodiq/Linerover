//
// Created by elmar on 23/05/2022.
//

#include "ScriptHandler.h"

ScriptHandler::ScriptHandler() : m_avoidObstacleScript{}, m_surpassSlopeScript{}, m_passedObstacle(false) {
}

ScriptHandler::~ScriptHandler() {
    delete ScriptHandler::instance;
}

ScriptHandler &ScriptHandler::configure() {
    return *(instance = new ScriptHandler{});
}

ScriptHandler &ScriptHandler::get() {
    return *instance;
}

AvoidObstacleScript &ScriptHandler::getAvoidObstacleScript() {
    return this->m_avoidObstacleScript;
}

SurpassSlopeScript &ScriptHandler::getSurpassSlopeScript() {
    return this->m_surpassSlopeScript;
}

bool &ScriptHandler::passedObstacle() {
    return this->m_passedObstacle;
}
//
// Created by elmar on 23/05/2022.
//

#include "ScriptHandler.h"

ScriptHandler::ScriptHandler() {
    //Logger::info("ScriptHandler has been enabled!");
}

ScriptHandler::~ScriptHandler() {
    delete ScriptHandler::instance;
}

ScriptHandler &ScriptHandler::configure() {
    if (instance == nullptr) return *(instance = new ScriptHandler{});

    //Logger::error("You are not allowed to configure a ScriptHandler twice!");
}

ScriptHandler &ScriptHandler::get() {
    if (instance != nullptr) return *instance;

    //Logger::error("You haven't configured a ScriptHandler yet!");
}

unsigned long &ScriptHandler::obstacleTime() {
    return this->m_obstacle_time;
}

unsigned long &ScriptHandler::slopeTime() {
    return this->m_slope_time;
}

int &ScriptHandler::obstaclePhase() {
    return this->m_obstacle_phase;
}

int &ScriptHandler::slopePhase() {
    return this->m_slope_phase;
}

bool &ScriptHandler::passedObstacle() {
    return this->m_passedObstacle;
}

void ScriptHandler::enableScript(Script *script) {
    m_scripts.push_back(script);
}

Script *ScriptHandler::getScript(const ScriptTarget &target) {
    for (const auto &script: m_scripts) {
        if (script->target() == target) return script;
    }

    return nullptr;
}


//
// Created by elmar on 23/05/2022.
//

#ifndef LINEROVER_AVOIDOBSTACLESCRIPT_H
#define LINEROVER_AVOIDOBSTACLESCRIPT_H

#include "../Script.h"


class AvoidObstacleScript : public Script {
private:
    unsigned long m_time = 0;
    int m_phase = 1;

public:
    AvoidObstacleScript() = default;

    ScriptTarget target() override {
        return ScriptTarget::AVOID_OBSTACLE;
    }

    State run() override;
};


#endif //LINEROVER_AVOIDOBSTACLESCRIPT_H

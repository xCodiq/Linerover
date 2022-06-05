//
// Created by elmar on 25/05/2022.
//

#ifndef LINEROVER_SURPASSSLOPESCRIPT_H
#define LINEROVER_SURPASSSLOPESCRIPT_H

#include "../Script.h"

class SurpassSlopeScript : public Script {
private:
    unsigned long m_time = 0;
    int m_phase = 1;

public:
    SurpassSlopeScript() = default;

    ScriptTarget target() override {
        return ScriptTarget::SURPASS_SLOPE;
    }

    State run() override;
};


#endif //LINEROVER_SURPASSSLOPESCRIPT_H

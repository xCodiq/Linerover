//
// Created by elmar on 23/05/2022.
//

#ifndef LINEROVER_SCRIPTHANDLER_H
#define LINEROVER_SCRIPTHANDLER_H

#include "module/controller/Controller.h"

#include "../Script.h"
#include "../implementation/AvoidObstacleScript.h"
#include "../implementation/SurpassSlopeScript.h"

class ScriptHandler {
private:
    // The instance pointer of the ScriptHandler
    static inline ScriptHandler *instance = nullptr;

    // The registered scripts which the Linerover can run while driving
    AvoidObstacleScript m_avoidObstacleScript;
    SurpassSlopeScript m_surpassSlopeScript;

    // Boolean variable is true if the Linerover passed the obstacle
    bool m_passedObstacle;

    explicit ScriptHandler();

    ~ScriptHandler();

public:
    ScriptHandler(ScriptHandler &) = delete;

    ScriptHandler &operator=(ScriptHandler &) = delete;

    /**
     * Configure the ScriptHandler which will instantiate the ScriptHandler instance
     *
     * @return the newly created script handler instance by reference
     */
    static ScriptHandler &configure();

    /**
     * Get the only instance of the ScriptHandler for the Linerover
     *
     * @return the instance of the ScriptHandler
     */
    static ScriptHandler &get();

    AvoidObstacleScript &getAvoidObstacleScript();

    SurpassSlopeScript &getSurpassSlopeScript();

    /**
     * Get/Set if the Linerover passed the obstacle
     *
     * @return true if the obstacle is passed, false otherwise
     */
    bool &passedObstacle();
};


#endif //LINEROVER_SCRIPTHANDLER_H

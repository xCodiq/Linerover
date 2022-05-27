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
    Vector<Script *> m_scripts = Vector<Script *>();

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

    /**
     * Tell the script handler to enable a script which
     * will be runnable while driving the Linerover
     *
     * @param script the script you want to enable
     */
    void enableScript(Script *script);

    /**
     * Get a script by a specific ScriptTarget
     *
     * @param target the script target of the script
     * @return the script of a specific ScriptTarget
     */
    Script *getScript(const ScriptTarget &target);
};


#endif //LINEROVER_SCRIPTHANDLER_H

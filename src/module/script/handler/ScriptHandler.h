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

    // Time and phase variables for obstacle and slope script
    unsigned long m_obstacle_time = 0, m_slope_time = 0;
    int m_obstacle_phase = 1, m_slope_phase = 1;

    // Boolean variable is true if the Linerover passed the obstacle
    bool m_passedObstacle = false;

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
     * Get/Set the obstacle script time in millis
     *
     * @return the obstacle time
     */
    unsigned long &obstacleTime();

    /**
     * Get/Set the slope script time in millis
     *
     * @return the slope time
     */
    unsigned long &slopeTime();

    /**
     * Get/Set the obstacle script phase
     *
     * @return the obstacle phase
     */
    int &obstaclePhase();

    /**
     * Get/Set the slope script phase
     *
     * @return the slope phase
     */
    int &slopePhase();

    /**
     * Get/Set if the Linerover passed the obstacle
     *
     * @return true if the obstacle is passed, false otherwise
     */
    bool &passedObstacle();

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

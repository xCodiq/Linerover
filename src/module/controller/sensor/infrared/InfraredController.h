//
// Created by elmar on 15/05/2022.
//

#ifndef LINEROVER_INFRAREDCONTROLLER_H
#define LINEROVER_INFRAREDCONTROLLER_H

#include "module/controller/Controller.h"
#include "module/controller/servo/Direction.h"


class InfraredController : public Controller {
private:
    // The instance pointer of the InfraredController
    static inline InfraredController *instance = nullptr;

    explicit InfraredController();

    ~InfraredController();

public:

    /**
     * Read a sensor specified by a sensor port
     * 
     * @param sensorPort the sensor port to read from 
     * @return true if the sensor read something, false otherwise
     */
    bool readSensor(int sensorPort);

public:
    InfraredController(InfraredController &) = delete;

    InfraredController &operator=(InfraredController &) = delete;

    /**
     * Configure the InfraredController which will instantiate the InfraredController instance
     *
     * @return the newly created infra controller instance by reference
     */
    static InfraredController &configure();

    /**
     * Get the only instance of the InfraredController for the Linerover
     *
     * @return the instance of the InfraredController
     */
    static InfraredController &get();

    /**
     * Check if the alignment of the Linerover using infrared sensors
     *
     * @return the new direction the linerover will point to based on the last sensor read
     */
    Direction checkAlignment();
};


#endif //LINEROVER_INFRAREDCONTROLLER_H

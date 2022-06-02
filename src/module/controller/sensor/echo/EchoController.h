//
// Created by elmar on 15/05/2022.
//

#ifndef LINEROVER_ECHOCONTROLLER_H
#define LINEROVER_ECHOCONTROLLER_H

#include "module/controller/Controller.h"
#include "Echo.h"

class EchoController : public Controller {
private:
    // Echo constants
    constexpr const static float SPEED_OF_SOUND = 0.034;
    const static int DISTANCE_LOWER_BOUND = 3;
    const static int DISTANCE_UPPER_BOUND = 45;

    // The instance pointer of the EchoController
    static inline EchoController *instance = nullptr;

    explicit EchoController();

    ~EchoController();

public:
    EchoController(EchoController &) = delete;

    EchoController &operator=(EchoController &) = delete;

    /**
     * Configure the EchoController which will instantiate the EchoController instance
     *
     * @return the newly created echo controller instance by reference
     */
    static EchoController &configure();

    /**
     * Get the only instance of the EchoController for the Linerover
     *
     * @return the instance of the EchoController
     */
    static EchoController &get();

    // return int; the distance
    /**
     * Let the Linerover use it's echo sensors to echo for nearby objects it's encountering
     *
     * @param echoLocation the echo sensor location to echo from
     * @return the distance of an encountering object
     */
    unsigned int echo(const Location &echoLocation);

    /**
     * Checks if an obstacle is near, based on logical checks, it will
     * determine if it's a BARRIER or a SLOPE
     *
     * @return the obstacle type the echo sensors detected
     */
    ObstacleType isObstacleNearby();
};


#endif //LINEROVER_ECHOCONTROLLER_H

//
// Created by elmar on 19/05/2022.
//

#ifndef LINEROVER_MOTORCONTROLLER_H
#define LINEROVER_MOTORCONTROLLER_H

#include "../../controller/Controller.h"
#include "MotorSpeed.h"

class MotorController : public Controller {
private:
    // The instance pointer of the MotorController
    static inline MotorController *instance = nullptr;

    explicit MotorController();

    ~MotorController();

public:
    MotorController(MotorController &) = delete;

    MotorController &operator=(MotorController &) = delete;

    /**
     * Configure the MotorController which will instantiate the MotorController instance
     *
     * @return the newly created motor controller instance by reference
     */
    static MotorController &configure();

    /**
     * Get the only instance of MotorController for hte Linerover
     *
     * @return the instance of the MotorController
     */
    static MotorController &get();

    /**
     * Adjust the motor speed (PWM) by passing in an integer as speed
     *
     * @param speed the speed number to change the motor speed to
     */
    void adjustSpeed(int speed);

    /**
     * The throttle function is used to make the Linerover drive and make sure
     * it's going forward and the motor-component stays activated
     *
     * @param state the current state of the Linerover
     */
    void throttle(const State &state);
};


#endif //LINEROVER_MOTORCONTROLLER_H

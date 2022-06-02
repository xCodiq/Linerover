//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_SERVOCONTROLLER_H
#define LINEROVER_SERVOCONTROLLER_H

#include "module/controller/Controller.h"
#include "Direction.h"
#include <Servo.h>


/**
 * The ServoController class
 *
 * Controls the Servo Motor, used for:
 * - Steering
 *
 * @see 'Servo.h' header file
 */
class ServoController : public Controller {
private:
    // The instance pointer of the ServoController
    static inline ServoController *instance = nullptr;

    // The servo pin port integer to write to
    int m_servoPort;

    // The Servo header instance to control the servo-component itself
    Servo m_servo;

    // The current direction the servo is pointing to
    Direction m_currentDirection = Direction::FORWARD,
    // The previous direction the servo was pointing to
    m_previousDirection = m_currentDirection;

    explicit ServoController(int servoPort);

    ~ServoController();

public:
    ServoController(ServoController &) = delete;

    ServoController &operator=(ServoController &) = delete;

    /**
     * Configure the ServoController which will instantiate the ServoController instance
     * 
     * @return the newly created servo controller instance by reference 
     */
    static ServoController &configure(int port);

    /**
     * Get the only instance of the ServoController for the Linerover
     *
     * @return the instance of the ServoController
     */
    static ServoController &get();

    /**
     * Update the servo-component using the Servo header instance
     */
    void update();

    /**
     * Change the direction of the servo motor, the motor controller will not change the
     * direction if the previous direction is equal to the specified direction
     *
     * In order for the change to take effect, the ServoController#update() function
     * has to be called to actually write to the Linerover hardware
     *
     * @param direction the new direction to steer to
     * @return true if updating was successful, false otherwise
     */
    bool changeDirection(const Direction &direction);
};


#endif //LINEROVER_SERVOCONTROLLER_H

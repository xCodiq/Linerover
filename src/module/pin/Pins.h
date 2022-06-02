//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_PINS_H
#define LINEROVER_PINS_H

#include <pins_arduino.h>

/**
 * The Pins class is our configuration class to let our program
 * know what pin-out layout we are using for all our components
 *
 * We used the standard Arduino pins that are available
 * on a regular Arduino UNO board with no modding
 */
class Pins {
public:
    // Serial monitor baud speed -> run: pio monitor
    static const int SERIAL_BAUD = 9600;

    // Servo motor port
    static const int SERVO_PORT = 2;

    // Infrared sensor ports
    static const int INFRARED_SENSOR_1_PORT = 3;
    static const int INFRARED_SENSOR_2_PORT = 4;
    static const int INFRARED_SENSOR_3_PORT = 10;
    static const int INFRARED_SENSOR_4_PORT = 6;
    static const int INFRARED_SENSOR_5_PORT = 7;

    // Echo sensor ports
    static const int ECHO_DATA_PORT = 8;
    static const int ECHO_TRIGGER_PORT = 9;
    static const int ECHO_DATA2_PORT = 10;
    static const int ECHO_TRIGGER2_PORT = 11;

    // Motor ports
    static const int MOTOR_ACTIVATION_PORT = A0;
    static const int MOTOR_SPEED_CONTROL_PORT = 5;
    static const int MOTOR_COUNTER_CLOCKWISE_PORT = A2;
    static const int MOTOR_CLOCKWISE_PORT = A3;

    // Available ports: 12, 13, A5
};


#endif //LINEROVER_PINS_H

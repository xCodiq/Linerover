//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_DIRECTION_H
#define LINEROVER_DIRECTION_H

#include <WString.h>

/**
 * The Direction enumeration will contain degrees for the Servo to
 * know how much to turn for each direction
 */
enum Direction {
    UNKNOWN = -69,
    FINISH = -420,
    SHARP_LEFT = 130,
    LEFT = 110 + 4, //118
    FORWARD = 100,
    RIGHT = 90 - 4, //88
    SHARP_RIGHT = 68
};

class DirectionUtil {
public:

    /**
     * Get the display name of a specific Direction enumeration
     *
     * @param direction the Direction to get it's display name of
     * @return the display name of the specific Direction
     */
    static String toNameString(const Direction &direction);
};


#endif //LINEROVER_DIRECTION_H

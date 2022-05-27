//
// Created by elmar on 06/04/2022.
//

#include "Direction.h"

String DirectionUtil::toNameString(const Direction &direction) {
    switch (direction) {
        case Direction::SHARP_LEFT:
            return "Sharp Left";
        case Direction::LEFT:
            return "Left";
        case Direction::FORWARD:
            return "Forward";
        case Direction::RIGHT:
            return "Right";
        case Direction::SHARP_RIGHT:
            return "Sharp Right";
        case Direction::UNKNOWN:
            return "Unknown";
    }
}
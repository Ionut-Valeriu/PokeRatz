//
// Created by ionut on 31.10.2024.
//

#ifndef ENUMS_H
#define ENUMS_H


////////// DESCRIPTION //////////
/// this header contains enum classes for efficiency

enum class Move {
    REVERSE = -1,
    STAY = 0,
    GO = 1
};

enum class Direction {
    UP = 'W',
    DOWN = 'S',
    LEFT = 'A',
    RIGHT = 'D'
};

enum class State {
    STAND = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,
    RIGHT = 4
};

#endif //ENUMS_H

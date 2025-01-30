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

enum class AnimationState {
    STAND = 0,
    UP,
    LEFT,
    DOWN,
    RIGHT
};

enum class ActionType {
    END = 0,
    START = 1
};

enum class Direction {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class ActionName {
    CLOSE,
    MOVE,
    PAUSE,
    SPRITES,
    SHAPES,
    ORIGIN,
    SUBMIT
};

enum class SceneManager {
    NONE = 0,
    FIRST,
    NEXT,
    PREVIOUS,
    LAST
};

#endif //ENUMS_H

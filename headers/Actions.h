//
// Created by ionut on 23.10.2024.
//

#ifndef ACTIONS_H
#define ACTIONS_H

////////// INCLUDE SECTION //////////
#include <string>

#include "Enums.h"

////////// DESCRIPTION //////////

/// this class is used to define the action that can take part in a scene
/// they are defined in init and specific to the scene, not the player/entity

////////// DEFINITION OF CLASS //////////
class Actions {
    ActionType m_type;
    ActionName m_name;
    Direction m_dir = Direction::NONE;

public:
    Actions(ActionType, const std::pair<ActionName, Direction> &);

    [[nodiscard]] ActionName name() const;

    [[nodiscard]] ActionType type() const;

    [[nodiscard]] Direction dir() const;
};

#endif //ACTIONS_H

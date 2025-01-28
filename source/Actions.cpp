//
// Created by ionut on 23.10.2024.
//

#include "Actions.h"

Actions::Actions(const ActionType type, const std::pair<ActionName, Direction> &detail)
    : m_type(type), m_name(detail.first), m_dir(detail.second) {
}

ActionName Actions::name() const { return m_name; }

ActionType Actions::type() const { return m_type; }

Direction Actions::dir() const { return m_dir; }

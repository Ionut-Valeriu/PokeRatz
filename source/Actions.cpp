//
// Created by ionut on 23.10.2024.
//

#include "../headers/Actions.h"

Actions::Actions() = default;

Actions::Actions(std::string name, std::string type) : m_name(std::move(name)), m_type(std::move(type)) {}

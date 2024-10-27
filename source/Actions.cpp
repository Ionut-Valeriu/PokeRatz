//
// Created by ionut on 23.10.2024.
//

#include "Actions.h"

Actions::Actions() : m_name("NONE"), m_type("NONE") {}

Actions::Actions(std::string name, std::string type) : m_name(std::move(name)), m_type(std::move(type)) {}

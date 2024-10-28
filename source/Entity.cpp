//
// Created by ionut on 22.10.2024.
//

#include "Entity.h"
#include <iostream>

Entity::Entity(size_t id, const std::string &tag) : m_id(id), m_tag(tag) {
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
}

void Entity::init() {
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(100, 100));
}

void Entity::draw(sf::RenderWindow &window) {
    tempShape->setPosition(m_position);
    window.draw(*tempShape);
}

void Entity::updatePos() {
    m_position += m_velocity;
}

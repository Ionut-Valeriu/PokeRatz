//
// Created by ionut on 22.10.2024.
//

#include "Entity.h"

Entity::Entity(size_t id, std::string tag) : m_id(id), m_tag(std::move(tag)) {
    // tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
    init();
}

void Entity::init() {
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(100, 100));
}

void Entity::draw(sf::RenderWindow &window) const {
    tempShape->setPosition(m_position);
    window.draw(*tempShape);
}

bool Entity::collide(const Entity &other) const {
    // todo
    return true;
}

void Entity::updatePos() {
    m_position += m_velocity;
}

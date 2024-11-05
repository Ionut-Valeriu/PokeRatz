//
// Created by ionut on 22.10.2024.
//

#include "Entity.h"

Entity::Entity(const size_t id, std::string tag) : m_tag(std::move(tag)), m_id(id) {
    // tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
    init();
}

void Entity::init() {
    m_transform = std::make_shared<CTransform>(sf::Vector2f{300,200}, sf::Vector2f{0,0});
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
}

void Entity::draw(sf::RenderWindow &window) const {
    tempShape->setPosition(m_transform->getPosition());
    window.draw(*tempShape);
}

bool Entity::collide(const Entity &other) const {
    // todo
    if (other.m_tag == m_tag) { return false; }
    return true;
}

float Entity::getX() const { return m_transform->getPosition().x; }
float Entity::getY() const { return m_transform->getPosition().y; }

float Entity::getWidth() const {
    return tempShape->getSize().x;
}

float Entity::getHeight() const {
    return tempShape->getSize().y;
}

void Entity::updatePos() const {
    if (m_transform->has()) {
        m_transform->setPosition(m_transform->getPosition() + m_transform->getVelocity());
    }
}

//
// Created by ionut on 22.10.2024.
//

#include "Entity.h"

Entity::Entity(const size_t id, std::string tag)
    : m_tag(std::move(tag)), m_id(id)
{
    init();
}

void Entity::init() {
    m_transform = std::make_shared<CTransform>(sf::Vector2f{300,200}, sf::Vector2f{0,0}, sf::Vector2f{5.0f, 5.0f});
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
    tempShape->setFillColor(sf::Color{0,0,0,0});
    tempShape->setOrigin(sf::Vector2f(50,50));
    tempShape->setOutlineColor(sf::Color{255,255,255,255});
    tempShape->setOutlineThickness(2);
}

void Entity::draw(sf::RenderWindow &window) const {
    tempShape->setPosition(m_transform->getPosition());
    m_animation->getSprite().setPosition(m_transform->getPosition());

    window.draw(*tempShape);
    window.draw(m_animation->getSprite());
    // window.draw(m_animation->getSprite());
}

std::shared_ptr<Animation> Entity::getAnimation() const {
    return m_animation;
}

bool Entity::collide(const Entity &other) const {
    // todo
    if (other.m_tag != m_tag) { return false; }
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

void Entity::setScale(const sf::Vector2f &scale) {
    m_transform->setScale(scale);
    // tempShape->setScale(scale);
}

sf::Vector2f Entity::getScale() const {
    return m_transform->getScale();
}

void Entity::updatePos() const {
    if (m_transform->has()) {
        m_transform->setPosition(m_transform->getPosition() + m_transform->getVelocity());
    }
}

void Entity::updateAnimation() const {
    m_animation->update();
}

void Entity::setAnimation(std::shared_ptr<Animation> anim) {
    m_animation = anim;
}

void Entity::setState(const State &state) {
    m_state = state;
}

void Entity::remove() {
    m_active = false;
}

std::ostream & operator<<(std::ostream &os, const Entity &obj) {
    return os
            << "\n m_id: " << obj.m_id << "; m_tag: " << obj.m_tag
            << "\n m_transform: " << obj.m_transform->getPosition().x
            << "\n tempShape: " << obj.tempShape << " size: " << sizeof(obj.tempShape)
            << "\n m_active: " << obj.m_active << " size: " << sizeof(obj.m_active)
            << "\n animation:" << obj.m_animation
            << "\n";
}

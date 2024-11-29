//
// Created by ionut on 22.10.2024.
//

#include "../headers/Entity.h"

Entity::Entity(const size_t id, std::string tag, const size_t drawLevel = 1)
    : m_tag(std::move(tag)), m_id(id), m_drawLevel(drawLevel)
{
    init();
}

void Entity::init() {
    m_transform = std::make_shared<CTransform>(sf::Vector2f{200,200},
        sf::Vector2f{0,0}, sf::Vector2f{5.0f, 5.0f});
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{80, 80});
    tempShape->setFillColor(sf::Color{0,0,0,0});
    tempShape->setOrigin(sf::Vector2f(40,40));
    tempShape->setOutlineColor(sf::Color{255,255,255,255});
    tempShape->setOutlineThickness(2);
}

void Entity::draw(sf::RenderWindow &window) const {
    tempShape->setPosition(m_transform->getPosition());
    m_animation->getSprite().setPosition(m_transform->getPosition());

    window.draw(*tempShape);
    window.draw(m_animation->getSprite());
}

std::shared_ptr<Animation> Entity::getAnimation() const {
    return m_animation;
}

bool Entity::collide(const Entity &other) const {
    // todo
    std::cout << "Entity::collide?\nCrr: " <<
        m_transform->getPosition().x << ", " << m_transform->getPosition().y <<
        "\nOth: " << other.m_transform->getPosition().x << ", " <<other.m_transform->getPosition().y <<"\n";
    if (m_transform->getPosition().x == other.m_transform->getPosition().x &&
        m_transform->getPosition().y == other.m_transform->getPosition().y)
    { return true; }
    return false;
}

float Entity::getX() const { return m_transform->getPosition().x; }
float Entity::getY() const { return m_transform->getPosition().y; }

float Entity::getWidth() const {
    return tempShape->getSize().x;
}

float Entity::getHeight() const {
    return tempShape->getSize().y;
}

void Entity::setScale(const sf::Vector2f &scale) const {
    m_transform->setScale(scale);
    // m_animation->setScale(scale);
    // tempShape->setScale(scale);
}

sf::Vector2f Entity::getScale() const {
    return m_transform->getScale();
}

void Entity::setPosition(const sf::Vector2f &position) const {
    m_transform->setPosition(position);
}

void Entity::setBorderT(const int thickness) const {
    tempShape->setOutlineThickness(static_cast<float>(thickness));
}

void Entity::updatePos() const {
    if (m_transform->has()) {
        m_transform->setPosition(m_transform->getPosition() + m_transform->getVelocity());
    }
}

void Entity::updateAnimation() const {
    m_animation->update();
}

void Entity::setAnimation(Animation &anim) {
    m_animation = std::make_shared<Animation>(anim);
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

//
// Created by ionut on 22.10.2024.
//

#include "Entity.h"

Entity::Entity(const size_t id, std::string tag, const sf::Texture& texture) : m_tag(std::move(tag)), m_id(id) {
    // tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
    init(texture);
}

void Entity::init(const sf::Texture& texture) {
    m_transform = std::make_shared<CTransform>(sf::Vector2f{300,200}, sf::Vector2f{0,0});
    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{100, 100});
    m_sprite.setTexture(texture);

    // texture is 16x16 pixels
    // i want it to be displayed as a 100x100 pixel
    // this is temporary
    m_sprite.setScale(100.0f/16.0f, 100.0f/16.0f);
}

void Entity::draw(sf::RenderWindow &window){
    // tempShape->setPosition(m_transform->getPosition());
    m_sprite.setPosition(m_transform->getPosition());
    // window.draw(*tempShape);
    window.draw(m_sprite);
    // window.draw(m_animation->getSprite());
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

void Entity::remove() {
    m_active = false;
}

std::ostream & operator<<(std::ostream &os, const Entity &obj) {
    return os
           << "\nm_id: " << obj.m_id << "; m_tag: " << obj.m_tag
           << "\nm_transform: " << obj.m_transform->getPosition().x
           << "\ntempShape: " << obj.tempShape << " size: " << sizeof(obj.tempShape)
           << "\nm_active: " << obj.m_active << " size: " << sizeof(obj.m_active)
        << "\nanimation:" << obj.m_animation
        << "\nsprite: " << obj.m_sprite.getTexture() << "\n";
}

//
// Created by ionut on 04.11.2024.
//

#include "../headers/Components.h"

// base component

bool Component::has() const {return m_exist;}

Component::Component(bool m_exist) : m_exist(m_exist) {}
Component::Component(const Component &other) = default;
Component &Component::operator=(const Component &other) {
    if (this == &other) return *this;
    m_exist = other.m_exist;
    return *this;
}

// transform component
const sf::Vector2f & CTransform::getPosition() const { return m_position; }
const sf::Vector2f & CTransform::getVelocity() const { return m_velocity; }
const sf::Vector2f & CTransform::getScale()    const { return m_scale;    }

void CTransform::setPosition(const sf::Vector2f &position) { m_position = position; }
void CTransform::setVelocity(const sf::Vector2f &velocity) { m_velocity = velocity; }
void CTransform::setScale(const sf::Vector2f &scale)       { m_scale = scale;       }

CTransform::CTransform(const sf::Vector2f &position, const sf::Vector2f &velocity, const sf::Vector2f &scale)
    : Component(true), m_position(position), m_velocity(velocity), m_scale(scale) {};
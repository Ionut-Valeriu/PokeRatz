//
// Created by ionut on 04.11.2024.
//

#include "Components.h"

// base component

bool Component::has() const {return m_exist;}

Component::Component(bool m_exist) : m_exist(m_exist) {}
Component::Component(const Component &other) : m_exist(other.m_exist) {}
Component &Component::operator=(const Component &other) {
    if (this == &other) return *this;
    m_exist = other.m_exist;
    return *this;
    auto aux = 1;
}

// transform component
const sf::Vector2f & CTransform::getPosition() const { return m_position; }
const sf::Vector2f & CTransform::getVelocity() const { return m_velocity; }

void CTransform::setPosition(const sf::Vector2f &position) { m_position = position; }
void CTransform::setVelocity(const sf::Vector2f &velocity) { m_velocity = velocity; }

CTransform::CTransform(const sf::Vector2f &m_position, const sf::Vector2f &m_velocity)
    : Component(true), m_position(m_position), m_velocity(m_velocity) {};
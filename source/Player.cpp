//
// Created by ionut on 22.10.2024.
//

#include "../headers/Player.h"
#include "../headers/Enums.h"

Player::Player(const size_t id, const std::string &tag, const size_t& drawLevel)
    : Entity(id, tag, drawLevel) {}

void Player::setVelocity(Move x, Move y) {
    if(x == Move::STAY || y == Move::STAY ) m_transform->setVelocity({0.0f, 0.0f});

    if (m_crrFrame > m_frameLastMove + m_updateSpeed) {
        m_frameLastMove = m_crrFrame;
        m_transform->setVelocity( {static_cast<float>(x) * m_speed, static_cast<float>(y) * m_speed} );
    }
}

void Player::incFrame() {
    m_crrFrame++;
}

// void Player::updatePos() {
//
// }
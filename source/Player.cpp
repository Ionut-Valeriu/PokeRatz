//
// Created by ionut on 22.10.2024.
//

#include "Player.h"
#include "Enums.h"

#include <iostream>

Player::Player(size_t id, const std::string &tag)
    : Entity(id, tag) {};

void Player::setVelocity(Move x, Move y) const {
    m_transform->setVelocity( {x * m_speed, y * m_speed} );
}

// void Player::updatePos() {
//
// }
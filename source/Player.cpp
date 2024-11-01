//
// Created by ionut on 22.10.2024.
//

#include "Player.h"
#include "Enums.h"

#include <iostream>

void Player::setVelocity(Move x, Move y) {
    m_velocity.x = x * m_speed;
    m_velocity.y = y * m_speed;
}

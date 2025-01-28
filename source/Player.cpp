//
// Created by ionut on 22.10.2024.
//

#include "../headers/Player.h"
#include "../headers/Enums.h"

Player::Player(const size_t id, const size_t &drawLevel)
    : Entity(id, drawLevel) {
}

void Player::setDirection(const Actions &a) {
    const bool mode = static_cast<bool>(a.type());
    switch (a.dir()) {
        case Direction::UP: {
            m_up = mode;
            break;
        }
        case Direction::DOWN: {
            m_down = mode;
            break;
        }
        case Direction::LEFT: {
            m_left = mode;
            break;
        }
        case Direction::RIGHT: {
            m_right = mode;
            break;
        }
        case Direction::NONE:
            break;
        default:
            // throw;
            break;
    }
}

void Player::setLeft() {
    if (m_transform->getScale().x > 0)
        m_transform->setScale({-m_transform->getScale().x, m_transform->getScale().y});
}

void Player::setRight() {
    if (m_transform->getScale().x < 0)
        m_transform->setScale({-m_transform->getScale().x, m_transform->getScale().y});
}


void Player::incFrame() { m_crrFrame++; }

void Player::onCollide(bool solid) {
    if (solid) m_transform->goToLastPos();
}

void Player::updatePos() {
    auto x = Move::STAY;
    auto y = Move::STAY;

    if (m_up) {
        m_state = State::UP;
        y = Move::REVERSE;
    } else if (m_down) {
        m_state = State::DOWN;
        y = Move::GO;
    } else if (m_left) {
        m_state = State::LEFT;
        x = Move::REVERSE;
    } else if (m_right) {
        m_state = State::RIGHT;
        x = Move::GO;
    }

    if (x == Move::STAY && y == Move::STAY) {
        m_state = State::STAND;
    }

    m_transform->setVelocity({0.0f, 0.0f});

    if (m_crrFrame > m_frameLastMove + m_updateSpeed) {
        m_frameLastMove = m_crrFrame;
        m_transform->setVelocity({static_cast<float>(x) * m_speed, static_cast<float>(y) * m_speed});
    }

    m_transform->updatePos();
}

void Player::showType(std::ostream &os) const {
    os << "Player\n";
}

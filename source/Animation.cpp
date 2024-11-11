//
// Created by ionut on 31.10.2024.
//

#include "Animation.h"

#include <cmath>
#include <utility>

Animation::Animation() = default;

Animation::Animation(const std::string &name, const sf::Texture &t)
    : Animation(name, t, 1, 0) {}

Animation::Animation (std::string name, const sf::Texture & t, size_t frameCount, size_t speed)
            : m_sprite(t)
            , m_name(std::move(name))
            , m_size (sf::Vector2f((float)t.getSize().x, (float)t.getSize().y))
            , m_frameCount(frameCount)
            , m_currentFrame(0)
            , m_speed(speed)
{
    m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
    m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, std::floor(m_size.x), std::floor(m_size.y)));
}

void Animation::update() {
    // todo

    m_currentFrame++;

    // todo calculate the frame of animation
    // todo set the texture rect
}

// bool Animation::hasEnded() const {
//     // todo - detect last frame
//     return false;
// }

const std::string & Animation::getName() const { return m_name; }

const sf::Vector2f & Animation::getSize() const { return m_size; }

sf::Sprite & Animation::getSprite() { return m_sprite; }

std::ostream & operator<<(std::ostream &os, const Animation &obj) {
    return os << "m_name: " << obj.m_name;
}

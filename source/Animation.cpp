//
// Created by ionut on 31.10.2024.
//

#include "../headers/Animation.h"

#include <cmath>
#include <iostream>
#include <utility>

Animation::Animation(const std::string &name, const sf::Texture &t)
    : Animation(name, t, 1, 0) {
}

Animation::Animation(std::string name, const sf::Texture &t, const size_t frameCount, const size_t speed)
    : m_sprite(t)
      , m_name(std::move(name))
      , m_size(sf::Vector2f(static_cast<float>(t.getSize().x), static_cast<float>(t.getSize().y)))
      , m_animationFrame(frameCount)
      , m_speed(speed) {
    m_sprite.setTextureRect(sf::IntRect(
        std::floor(static_cast<float>(m_gameFrame) * m_size.x), 0,
        std::floor(m_size.x / static_cast<float>(frameCount)),
        std::floor(m_size.y)
    ));
    m_sprite.setOrigin(m_size.x / static_cast<float>(frameCount) / 2.0f, m_size.y / 2.0f);
    m_sprite.setScale(m_scale);
}

void Animation::update() {
    m_gameFrame++;

    const auto animFrame = static_cast<int>(m_gameFrame / m_speed) % m_animationFrame;

    m_sprite.setTextureRect({
        static_cast<int>(static_cast<float>(animFrame) * m_size.x / static_cast<float>(m_animationFrame)),
        0,
        static_cast<int>(m_size.x / static_cast<float>(m_animationFrame)),
        static_cast<int>(m_size.y)
    });

    m_sprite.setScale(m_scale);
}

const std::string &Animation::getName() const { return m_name; }

const sf::Vector2f &Animation::getSize() const { return m_size; }

sf::Sprite &Animation::getSprite() { return m_sprite; }

void Animation::setScale(const sf::Vector2f &scale) {
    m_scale = scale;
    m_sprite.scale(m_scale.x, m_scale.y);
    if (m_sprite.getTexture()->isRepeated())
        m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(scale.x), static_cast<int>(scale.y)));
}

void Animation::setRect(const sf::IntRect &rect) {
    m_sprite.setTextureRect(rect);
    m_sprite.setOrigin({static_cast<float>(rect.width) / 2.0f, static_cast<float>(rect.height) / 2.0f});
}

std::ostream &operator<<(std::ostream &os, const Animation &obj) {
    return os << "animation: " << obj.m_name << ", speed: " << obj.m_speed
           << ", frameCount: " << obj.m_animationFrame << "\n";
}

//
// Created by ionut on 31.10.2024.
//

#ifndef ANIMATION_H
#define ANIMATION_H

////////// INCLUDE SECTION //////////
#include <SFML/Graphics.hpp>
#include <string>

////////// DESCRIPTION //////////

/// this class will manage an animation
/// will move the rectangle of sprite over the texture
/// to create the illusion of moving
/// will have m_speed which determine

////////// DEFINITION OF CLASS //////////
class Animation {
    // size 288
    sf::Sprite m_sprite;

    // size 32
    std::string m_name = "none";

    // size 8
    sf::Vector2f m_size = { 1, 1 };
    sf::Vector2f m_scale = { 5.0f, 5.0f };
    size_t m_animationFrame = 1;
    size_t m_gameFrame = 0;
    size_t m_speed = 1;

public:
    // constructors
    Animation() = default;
    Animation (const std::string &name, const sf::Texture &t); // static sprite
    Animation (std::string name, const sf::Texture &t, size_t frameCount, size_t speed); // moving animation

    // methods
    void update();

    // getters
    const std::string &getName() const;
    const sf::Vector2f &getSize() const;
    sf::Sprite &getSprite();

    // setters
    void setScale (const sf::Vector2f &scale);
    void setRect (const sf::IntRect &rect);

    friend std::ostream & operator<<(std::ostream &os, const Animation &obj);
};

#endif //ANIMATION_H

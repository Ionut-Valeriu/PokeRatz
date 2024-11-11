//
// Created by ionut on 31.10.2024.
//

#ifndef ANIMATION_H
#define ANIMATION_H

////////// INCLUDE SECTION //////////
#include <SFML/Graphics.hpp>
////////// DESCRIPTION //////////

////////// DEFINITION OF CLASS //////////
class Animation {
    // 288
    sf::Sprite m_sprite;

    // 32
    std::string m_name = "none";

    // 8
    sf::Vector2f m_size = { 1, 1 };
    size_t m_frameCount = 1;
    size_t m_currentFrame = 0;
    size_t m_speed = 0;

public:
    // constructors
    Animation();
    Animation (const std::string &name, const sf::Texture &t);
    Animation (std::string name, const sf::Texture &t, size_t frameCount, size_t speed);

    // methods
    void update();
    // bool hasEnded() const;

    // getters
    const std::string &getName() const;
    const sf::Vector2f &getSize() const;
    sf::Sprite &getSprite();

    friend std::ostream & operator<<(std::ostream &os, const Animation &obj);
};

#include <string>


#endif //ANIMATION_H

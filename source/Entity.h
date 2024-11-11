//
// Created by ionut on 22.10.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

////////// INCLUDE SECTION //////////
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Components.h"

////////// DESCRIPTION //////////

/// this class will be used to spawn any entity in the game
/// those entities have different properties like:
/// - id (unique)
/// - tag (category)
/// - position
/// - velocity
/// - sprite & hit-box (current rectangular shape)
/// - different properties
/// also a method for every aspect of the game
/// (this is the aiming point, currently not finished)

////////// DEFINITION OF CLASS //////////
class Entity {
protected:
    // size 32
    std::string m_tag = "default";

    // size 16
    std::shared_ptr<CTransform> m_transform;
    std::shared_ptr<sf::RectangleShape> tempShape;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    // size 8
    size_t m_id;

    // size 1
    bool m_active = true;

    Animation m_animation;

public:
    Entity(size_t id, std::string tag, const sf::Texture& texture);

    void init(const sf::Texture& texture);

    void draw(sf::RenderWindow &window);

    // getters
    [[nodiscard]] size_t id() const { return m_id; }
    [[nodiscard]] const std::string &tag() const { return m_tag; }
    [[nodiscard]] bool active() const { return m_active; }

    // other methods
    [[nodiscard]] bool collide(const Entity &other) const;

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;

    void updatePos() const;
    void remove();

    friend std::ostream & operator<<(std::ostream &os, const Entity &obj);
};



#endif //ENTITY_H

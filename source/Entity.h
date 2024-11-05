//
// Created by ionut on 22.10.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

////////// INCLUDE SECTION //////////
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Components.h"

////////// DESCRIPTION //////////

/// this class will be used to spawn any entity in the game
/// those entities have different properties like:
/// - id (unique)
/// - tag (category)
/// - position
/// - velocity
/// - sprite & hit-box (current rectangular sha[e)
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

    // size 8
    size_t m_id;

    // size 1
    bool m_active = true;

    friend std::ostream & operator<<(std::ostream &os, const Entity &obj) {
        return os
        << "m_id: " << obj.m_id << "; m_tag: " << obj.m_tag
        << "\nm_transform: " << obj.m_transform->getPosition().x
        << "\ntempShape: " << obj.tempShape << " size: " << sizeof(obj.tempShape)
        << "m_active: " << obj.m_active << " size: " << sizeof(obj.m_active);
    }

public:
    Entity(size_t id, std::string tag);

    void init();

    void draw(sf::RenderWindow &window) const;

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
};



#endif //ENTITY_H

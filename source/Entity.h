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
#include "Enums.h"

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
    State m_state = State::STAND;

    // size 16
    std::shared_ptr<CTransform> m_transform;
    std::shared_ptr<sf::RectangleShape> tempShape;
    std::shared_ptr<Animation> m_animation;

    // size 8
    size_t m_id;

    // size 1
    bool m_active = true;

public:
    Entity(size_t id, std::string tag);

    void init();

    void draw(sf::RenderWindow &window) const;

    // getters
    [[nodiscard]] size_t id() const { return m_id; }
    [[nodiscard]] const std::string &tag() const { return m_tag; }
    [[nodiscard]] bool active() const { return m_active; }
    [[nodiscard]] State state() const { return m_state; }
    [[nodiscard]] std::shared_ptr<Animation> getAnimation() const;

    // other methods
    [[nodiscard]] bool collide(const Entity &other) const;

    // transform methods
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    void setScale (const sf::Vector2f &scale);
    sf::Vector2f getScale() const;

    // setters
    void setAnimation(std::shared_ptr<Animation> anim);
    void setState(const State &state);

    // updates
    void updatePos() const;
    void updateAnimation() const;

    void remove();

    friend std::ostream & operator<<(std::ostream &os, const Entity &obj);
};



#endif //ENTITY_H

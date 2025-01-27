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
    State m_state = State::STAND;

    // size 16
    std::shared_ptr<CTransform> m_transform;
    std::shared_ptr<CBoundingBox> m_boundingBox;
    std::shared_ptr<sf::RectangleShape> tempShape;
    std::shared_ptr<sf::CircleShape> m_origin;
    std::shared_ptr<Animation> m_animation;

    // size 8
    size_t m_id;
    size_t m_drawLevel; // 1 is first render (ex: background), the higher number = the closest to the camera

    // size 1
    bool m_active = true;
    bool m_solid = true; // this will push the player back

public:
    Entity(size_t id, size_t drawLevel);

    void init();

    void setRect(sf::IntRect rect);

    void draw(sf::RenderWindow &window, bool s, bool r, bool o) const;

    // getters
    [[nodiscard]] size_t id() const { return m_id; }
    [[nodiscard]] size_t level() const { return m_drawLevel; }
    [[nodiscard]] bool active() const { return m_active; }
    [[nodiscard]] State state() const { return m_state; }

    [[nodiscard]] std::shared_ptr<Animation> getAnimation() const;

    // other methods
    [[nodiscard]] bool collide(const Entity &other) const;

    virtual void onCollide(bool solid) = 0;

    // transform methods
    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getWidth() const;

    [[nodiscard]] float getHeight() const;

    [[nodiscard]] sf::Vector2f getScale() const;


    // setters
    void setScale(const sf::Vector2f &scale) const;

    void setPosition(const sf::Vector2f &position) const;

    void setAnimation(Animation &anim);

    void setSolidity(bool solid);

    // updates
    virtual void updatePos();

    void updateAnimation() const;

    [[nodiscard]] bool isSolid() const;

    // [[nodiscard]] bool isRemovable() const;

    void remove();

    virtual ~Entity() = default;

    friend std::ostream &operator<<(std::ostream &os, const Entity &obj);

private:
    virtual void showType(std::ostream &os) const;
};


#endif //ENTITY_H

//
// Created by ionut on 04.11.2024.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

////////// INCLUDE SECTION //////////
#include <iostream>
#include <SFML/Graphics.hpp>

////////// DESCRIPTION //////////

/// the component base class will simply tell if a specific derived component exist
/// because every component should be marked if it is used or not in a specific entity
/// by default it is marked as not existed, but modified in the constructor of every derived component

////////// DEFINITION OF CLASS //////////
class Component {
protected:
    bool m_exist = false;
public:
    [[nodiscard]] bool has () const;

    Component() = default;
    explicit Component(bool m_exist);

    Component(const Component &other);
    Component & operator=(const Component &other);

    friend std::ostream & operator<<(std::ostream &os, const Component &obj) {
        return os << "m_exist: " << obj.m_exist;
    }

    ~Component() = default;
};

////////// DESCRIPTION //////////

/// the transform class will contain the position and velocity of an entity

////////// DEFINITION OF CLASS //////////
class CTransform : public Component {
public:
    CTransform() = default;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_scale;

public:
    [[nodiscard]] const sf::Vector2f &getPosition() const;
    [[nodiscard]] const sf::Vector2f &getVelocity() const;
    [[nodiscard]] const sf::Vector2f &getScale() const;

    void setPosition(const sf::Vector2f &position);
    void setVelocity(const sf::Vector2f &velocity);
    void setScale(const sf::Vector2f &scale);

    CTransform(const sf::Vector2f &position, const sf::Vector2f &velocity, const sf::Vector2f &scale);
};

////////// DESCRIPTION //////////

///

////////// DEFINITION OF CLASS //////////
class CBoundingBox
{
public:
    sf::CircleShape circle;

    CBoundingBox(float radius, int points, const sf::Color & fill, const sf::Color outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

#endif //COMPONENTS_H

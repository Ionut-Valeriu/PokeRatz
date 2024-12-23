//
// Created by ionut on 04.11.2024.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

////////// INCLUDE SECTION //////////
#include <SFML/Graphics.hpp>

////////// DESCRIPTION //////////

/// the component base class will simply tell if a specific derived component exist
/// because every component should be marked if it is used or not in a specific entity
/// by default it is marked as not existed, but modified in the constructor of every derived component

////////// DEFINITION OF CLASS //////////
class Component {
protected:
    bool m_exist;

public:
    // constructors & operators & destructors
    explicit Component(bool m_exist = true);

    Component(const Component &other);

    Component &operator=(const Component &other);

    ~Component() = default;

    // other functions
    [[nodiscard]] bool has() const;

    friend std::ostream &operator<<(std::ostream &os, const Component &obj) {
        return os << "m_exist: " << obj.m_exist;
    }
};

////////// DESCRIPTION //////////

/// the transform class will contain the position and velocity of an entity

////////// DEFINITION OF CLASS //////////
class CTransform : public Component {
    sf::Vector2f m_position;
    sf::Vector2f m_lastPos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_scale;

public:
    CTransform() = default;

    CTransform(const sf::Vector2f &position, const sf::Vector2f &velocity, const sf::Vector2f &scale);

    // getters
    [[nodiscard]] const sf::Vector2f &getPosition() const;

    [[nodiscard]] const sf::Vector2f &getScale() const;

    // setters
    void setPosition(const sf::Vector2f &position);

    void setVelocity(const sf::Vector2f &velocity);

    void setScale(const sf::Vector2f &scale);

    // other functions
    void updatePos();

    void goToLastPos();
};

////////// DESCRIPTION //////////

///

////////// DEFINITION OF CLASS //////////
class CBoundingBox : public Component {
    sf::IntRect m_boundingRect;

public:
    CBoundingBox() = default;

    // [[nodiscard]] sf::IntRect getBoundingRect() const {
    //     return m_boundingRect;
    // }

    void setBoundingRect(const sf::IntRect &m_bounding_box) {
        m_boundingRect = m_bounding_box;
    }
};

#endif //COMPONENTS_H

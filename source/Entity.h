//
// Created by ionut on 22.10.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

////////// INCLUDE SECTION //////////
#include <memory>
#include <SFML/Graphics.hpp>

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

    bool m_active = true;
    size_t m_id;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    std::string m_tag = "default";

    Entity(size_t id, std::string tag);

    std::shared_ptr<sf::RectangleShape> tempShape;

    // std::ostream& operator<<(std::ostream &os) const {
    //     os << e.m_id << " (" << e.m_tag << ")";
    //     return os;
    // }

public:
    void init();
    void draw(sf::RenderWindow& window) const;

    bool collide(const Entity& other) const;

    void updatePos();
};



#endif //ENTITY_H

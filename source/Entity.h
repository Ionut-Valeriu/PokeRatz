//
// Created by ionut on 22.10.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

#include "SFML/Graphics.hpp"

class EntityManager;

class Entity {
protected:
    friend class EntityManager;

    bool m_active = true;
    size_t m_id;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    std::string m_tag = "default";

    Entity(size_t id, const std::string &tag);


    /// todo
    ///temp
    std::shared_ptr<sf::RectangleShape> tempShape;

    // std::ostream& operator<<(std::ostream &os) const {
    //     os << e.m_id << " (" << e.m_tag << ")";
    //     return os;
    // }

public:
    void init();
    void draw(sf::RenderWindow& window);

    void updatePos();
};



#endif //ENTITY_H

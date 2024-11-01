//
// Created by ionut on 22.10.2024.
//

#ifndef PLAYER_H
#define PLAYER_H

////////// INCLUDE SECTION //////////
#include "Entity.h"
#include "Actions.h"
#include "Enums.h"

////////// DESCRIPTION //////////
/// extended version of Entity class, add the following functions:
/// - movement



////////// DEFINITION OF CLASS //////////
class Player : public Entity{
    int m_speed;

    bool m_up = false;
    bool m_down = false;
    bool m_left = false;
    bool m_right = false;

public:

    Player(size_t id, const std::string &tag, const int speed = 3)
        : Entity(id, tag), m_speed(speed) {};

    //getters
    bool up()    const { return m_up;    }
    bool down()  const { return m_down;  }
    bool left()  const { return m_left;  }
    bool right() const { return m_right; }

    // setters
    void setUp    (bool up)    { this->m_up    = up;    }
    void setDown  (bool down)  { this->m_down  = down;  }
    void setLeft  (bool left)  { this->m_left  = left;  }
    void setRight (bool right) { this->m_right = right; }

    // methods
    void setVelocity(Move x, Move y);
};


#endif //PLAYER_H

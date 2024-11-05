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
    // speed equal to size so it snaps when move
    float m_speed = tempShape->getSize().x;

    bool m_up = false;
    bool m_down = false;
    bool m_left = false;
    bool m_right = false;

public:

    Player(size_t id, const std::string &tag);

    //getters
    [[nodiscard]] bool up()    const { return m_up;    }
    [[nodiscard]] bool down()  const { return m_down;  }
    [[nodiscard]] bool left()  const { return m_left;  }
    [[nodiscard]] bool right() const { return m_right; }
    [[nodiscard]] float speed()const { return m_speed; }

    // setters
    void setUp    (bool up)    { this->m_up    = up;    }
    void setDown  (bool down)  { this->m_down  = down;  }
    void setLeft  (bool left)  { this->m_left  = left;  }
    void setRight (bool right) { this->m_right = right; }

    // methods
    void setVelocity(Move x, Move y) const;

    // void updatePos();
};

#endif //PLAYER_H

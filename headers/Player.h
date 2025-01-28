//
// Created by ionut on 22.10.2024.
//

#ifndef PLAYER_H
#define PLAYER_H

////////// INCLUDE SECTION //////////
#include "Actions.h"
#include "Entity.h"
#include "Enums.h"

////////// DESCRIPTION //////////

/// child of Entity class, implementing the player with movement

////////// DEFINITION OF CLASS //////////
class Player final : public Entity {
    // speed equal to size so it snaps when move
    // todo
    float m_speed = tempShape->getSize().x;

    size_t m_crrFrame = 0;
    size_t m_frameLastMove = 0;

    int m_updateSpeed = 5;

    bool m_up = false;
    bool m_down = false;
    bool m_left = false;
    bool m_right = false;

public:
    explicit Player(size_t id, const size_t &drawLevel = 3);

    void setDirection(const Actions &);

    void setLeft();

    void setRight();

    void incFrame();

    void onCollide(bool solid) override;

private:
    void updatePos() override;

    void showType(std::ostream &os) const override;
};

#endif //PLAYER_H

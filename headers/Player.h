//
// Created by ionut on 22.10.2024.
//

#ifndef PLAYER_H
#define PLAYER_H

////////// INCLUDE SECTION //////////
#include "Entity.h"
#include "Enums.h"

////////// DESCRIPTION //////////
/// extended version of Entity class, add the following functions:
/// - movement

////////// DEFINITION OF CLASS //////////
class Player : public Entity {
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
    explicit Player(size_t id,const size_t &drawLevel = 3);

    //getters
    [[nodiscard]] bool up() const { return m_up; }
    [[nodiscard]] bool down() const { return m_down; }
    [[nodiscard]] bool left() const { return m_left; }
    [[nodiscard]] bool right() const { return m_right; }
    // [[nodiscard]] float speed()const { return m_speed; }

    // setters
    void setUp(const bool up) { this->m_up = up; }
    void setDown(const bool down) { this->m_down = down; }
    void setLeft(const bool left) { this->m_left = left; }
    void setRight(const bool right) { this->m_right = right; }

    // methods
    void setVelocity(Move x, Move y);

    void incFrame();

    void onCollide(bool solid) override;

private:
    void showTip(std::ostream &os) const override;
};

#endif //PLAYER_H

//
// Created by ionut on 22.10.2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Actions.h"


class Player : public Entity{
    float m_speed = 3;

public:
    Player(size_t id, const std::string &tag)
        : Entity(id, tag)
    {
        init();
    }

    void setAction (Actions& action);
};



#endif //PLAYER_H

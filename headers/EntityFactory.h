//
// Created by ionut on 12.01.2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <memory>

#include "Entity.h"
#include "Player.h"


class EntityFactory {
    static std::shared_ptr<Entity> makePlayer(size_t id);

    static std::shared_ptr<Entity> makeMonster(size_t id);

    static std::shared_ptr<Entity> makeBackground(size_t id);

public:
    static std::shared_ptr<Entity> makeEntity(char type, size_t id);

    static std::shared_ptr<Player> make_Player(size_t id);
};


#endif //ENTITYFACTORY_H

//
// Created by ionut on 12.01.2025.
//

#include "../headers/EntityFactory.h"
#include "Player.h"
#include "Monster.h"
#include "Background.h"
#include "EntityManager.h"

std::shared_ptr<Entity> EntityFactory::makePlayer(size_t id) {
    return std::make_shared<Player>(id, 3);
}

std::shared_ptr<Entity> EntityFactory::makeMonster(size_t id) {
    return std::make_shared<Monster>(id, 2);
}

std::shared_ptr<Entity> EntityFactory::makeBackground(size_t id) {
    return std::make_shared<Background>(id, 1);
}

std::shared_ptr<Entity> EntityFactory::makeEntity(char type, size_t id) {
    switch (type) {
        case '-': return nullptr;

        case 'P': return makePlayer(id);

        case 'M': return makeMonster(id);

        case 'B': return makeBackground(id);

        default: throw std::invalid_argument("Invalid type: " + std::to_string(type));
    }
}

std::shared_ptr<Player> EntityFactory::make_Player(size_t id) {
    return std::make_shared<Player>(id);
}



//
// Created by ionut on 12.01.2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

////////// INCLUDE SECTION //////////
#include <memory>

#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Background.h"

////////// DESCRIPTION //////////

/// Specialize class for creating entity and his descendants

////////// DEFINITION OF CLASS //////////
class EntityFactory {
    template<class T>
    static std::shared_ptr<Entity> addEntity(const size_t &id);

public:
    static std::shared_ptr<Entity> makeEntity(char type, size_t id);
};

#include "../source/EntityFactory.cpp"

#endif //ENTITYFACTORY_H

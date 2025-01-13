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
template <class E>
class EntityFactory {
    template<typename T>
    static std::shared_ptr<E> addEntity(const size_t &id, size_t drawLevel);

public:
    static std::shared_ptr<E> makeEntity(char type, size_t id, size_t drawLevel);
};



#include "../source/EntityFactory.cpp"

#endif //ENTITYFACTORY_H

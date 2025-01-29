//
// Created by ionut on 12.01.2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

////////// INCLUDE SECTION //////////
#include <memory>



////////// DESCRIPTION //////////

/// Specialize class for creating entity and his descendants

////////// DEFINITION OF CLASS //////////
template<class E>
class Factory {
    template<typename T>
    static std::shared_ptr<E> addEntity(const size_t &id, size_t drawLevel);

    template<typename T>
    static std::shared_ptr<E> addScene();

public:
    static std::shared_ptr<E> makeEntity(char type, size_t id, size_t drawLevel);

    static std::shared_ptr<E> makeScene(const std::string &name);
};

#include "../source/Factory.cpp"

#endif //ENTITYFACTORY_H

//
// Created by ionut on 12.01.2025.
//

//#include "Scenes/MenuScene.h"
//#include "Scenes/PlayScene.h"

#include "Player.h"
#include "Monster.h"
#include "Background.h"
#include "Illusion.h"

/// for entity tree
template <class E>
template <typename T>
std::shared_ptr<E> Factory<E>::addEntity(const size_t &id, size_t drawLevel) {
    auto e = std::make_shared<T>(id, drawLevel);
    return e;
}

/// UPDATE JUST HERE (IN SWITCH) FOR NEW DERIVED CLASSES FROM ENTITY
template <class E>
std::shared_ptr<E> Factory<E>::makeEntity(char type, size_t id, size_t drawLevel) {
    switch (type) {
        case '-': return nullptr;

        case 'P': return addEntity<Player>(id, drawLevel);

        case 'M': return addEntity<Monster>(id, drawLevel);

        case 'B': return addEntity<Background>(id, drawLevel);

        case 'I': return addEntity<Illusion>(id, drawLevel);

        default: throw std::invalid_argument("Invalid type: " + std::to_string(type));
    }
}
//////////////////////////////////////////////////

/// for scene tree
template <class E>
template <typename T>
std::shared_ptr<E> Factory<E>::addScene() {
    auto e = std::make_shared<T>();
    return e;
}

/// UPDATE JUST HERE (IN SWITCH) FOR NEW DERIVED CLASSES FROM SCENE
template <class E>
std::shared_ptr<E> Factory<E>::makeScene(const std::string &name) {
    const char c = name[0];
    switch (c) {
        case '-': return nullptr;

        default: throw std::invalid_argument("Invalid type: " + name);
    }
}

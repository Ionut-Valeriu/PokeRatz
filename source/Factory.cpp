//
// Created by ionut on 12.01.2025.
//

#include "Scenes/MenuScene.h"
#include "Scenes/PlayScene.h"

#include "Player.h"
#include "Monster.h"
#include "Background.h"
#include "Illusion.h"

/// for entity tree
template<class E>
template<typename T>
std::shared_ptr<E> Factory<E>::addEntity(const size_t &id, size_t drawLevel) {
    auto e = std::make_shared<T>(id, drawLevel);
    return e;
}

/// UPDATE JUST HERE (IN SWITCH) FOR NEW DERIVED CLASSES FROM ENTITY
template<class E>
std::shared_ptr<E> Factory<E>::makeEntity(char type, size_t id, size_t drawLevel) {
    switch (type) {
        case '-': return nullptr;

        case 'B': return addEntity<Background>(id, drawLevel);

        case 'I': return addEntity<Illusion>(id, drawLevel);

        case 'M': return addEntity<Monster>(id, drawLevel);

        case 'P': return addEntity<Player>(id, drawLevel);

        default: throw std::invalid_argument("Invalid type: " + std::to_string(type));
    }
}

//////////////////////////////////////////////////

/// for scene tree
template<class E>
template<typename T>
std::shared_ptr<E> Factory<E>::addScene(std::string file, sf::RenderWindow &window) {
    auto s = std::make_shared<T>(file, window);
    return s;
}

/// UPDATE JUST HERE (IN SWITCH) FOR NEW DERIVED CLASSES FROM SCENE
template<class E>
std::shared_ptr<E> Factory<E>::makeScene(const std::string &name, char type, std::string file,
                                         sf::RenderWindow &window) {
    switch (type) {
        case '-': return nullptr;

        case 'P': return addScene<PlayScene>(file, window);

        case 'M': return addScene<MenuScene>(file, window);

        default: throw std::invalid_argument("Invalid type: " + name);
    }
}

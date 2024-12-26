//
// Created by ionut on 22.10.2024.
//

#include "EntityManager.h"

#include <memory>
#include <iostream>

#include "Player.h"

size_t EntityManager::m_entitiesSpawned = 1;

void EntityManager::update() {
    // adding new entities
    for (auto &e: m_entitiesToAdd) {
        std::cout << "Entity added: " << e->id() << "\n";
        m_entities.push_back(e);
        m_entityDrawMap[e->level()].push_back(e);
    }
    m_entitiesToAdd.clear();

    // removing old entities
    removeDeadEntities(m_entities);

    for (auto &[drawLevel, entityVec]: m_entityDrawMap) {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec) {
    std::erase_if(vec, [](const std::shared_ptr<Entity> &e) {
        return !e->active();
    });
}

// template<class T>
// std::shared_ptr<T> EntityManager::addEntity(const size_t &drawLevel) {
//     m_maxDrawLevel = m_maxDrawLevel < drawLevel ? drawLevel : m_maxDrawLevel;
//
//     auto e = std::make_shared<T>(m_entitiesSpawned++, drawLevel);
//
//     m_entitiesToAdd.push_back(e);
//     return e;
// }
//
// template std::shared_ptr<Player> EntityManager::addEntity<Player>(const size_t &drawLevel);
//
// template std::shared_ptr<Background> EntityManager::addEntity<Background>(const size_t &drawLevel);
//
// template std::shared_ptr<Monster> EntityManager::addEntity<Monster>(const size_t &drawLevel);

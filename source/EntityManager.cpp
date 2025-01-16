//
// Created by ionut on 22.10.2024.
//

#include "EntityManager.h"

#include <memory>
#include <iostream>

#include "Player.h"

size_t EntityManager::m_entitiesSpawned = 1;
size_t EntityManager::m_maxDrawLevel = 3;

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

size_t EntityManager::getEntityCount() {
    return m_entitiesSpawned++;
}

std::shared_ptr<Player> EntityManager::load(const std::string &fileName,
    const LevelLoader &levelLoader,
    sf::RenderWindow &rWindow) {
    return levelLoader.fill(m_entitiesToAdd, fileName, rWindow);
}

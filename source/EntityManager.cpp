//
// Created by ionut on 22.10.2024.
//

#include "EntityManager.h"

#include <memory>
#include <iostream>

void EntityManager::update() {
    // adding new entities
    for (auto& e : m_entitiesToAdd) {
        std::cout << "Entity added: " << e->id() << "\n";
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_entitiesToAdd.clear();

    // removing old entities
    removeDeadEntities(m_entities);

    for (auto& [tag, entityVec] : m_entityMap) {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec& vec) {
    auto newEnd = std::ranges::remove_if(vec, [](const std::shared_ptr<Entity> &e) {
        return !e->active();
    }).begin();

    vec.erase(newEnd, vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    auto e = std::make_shared<Entity>(Entity{m_entityNumber++, tag});

    m_entitiesToAdd.push_back(e);

    return e;
}

std::shared_ptr<Player> EntityManager::addPlayer(const std::string &tag) {
    auto e = std::make_shared<Player>(m_entityNumber++, tag);

    m_entitiesToAdd.push_back(e);

    return e;
}

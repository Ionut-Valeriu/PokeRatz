//
// Created by ionut on 22.10.2024.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Entity.h"
#include "Player.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;
    size_t m_entityNumber = 1;

public:
    void update();
    void removeDeadEntities(EntityVec& vec);

    std::shared_ptr<Entity> addEntity(const std::string& tag);
    std::shared_ptr<Player> addPlayer(const std::string& tag);

    const EntityVec getEntities() { return m_entities; }
    EntityVec getEntities(const std::string& tag) { return m_entityMap[tag]; }

};



#endif //ENTITYMANAGER_H

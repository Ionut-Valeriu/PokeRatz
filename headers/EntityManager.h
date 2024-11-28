//
// Created by ionut on 22.10.2024.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

////////// INCLUDE SECTION //////////
#include <map>
#include <string>
#include <vector>

#include "Entity.h"
#include "Player.h"

////////// DESCRIPTION //////////

/// this class manage the entities in those modes:
/// - create new entities and:
/// --1 add them to a vector of active entities
/// --2 add them to a vector inside of map, by their tag
///     this action optimize the search of a specific entity category
/// --3 remove dead entities and resize some of the vectors
/// --4 give each entity a unique id (m_entitiesSpawned)
///     this variable counts how many entities we have spawned in the entire game

////////// SHORTCUTS //////////
typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

////////// DEFINITION OF CLASS //////////
class EntityManager {
    // size 48
    EntityMap m_entityMap;     // the entity map on the 2nd point in the description

    // size 24
    EntityVec m_entities;      // vector to store all current entities
    EntityVec m_entitiesToAdd; // vector to store entities that will be added // this evicts some bugs

    // size 8
    size_t m_entitiesSpawned = 1;

public:
    void update(); // adding and removing entities
    static void removeDeadEntities(EntityVec& vec); // this is called in update

    std::shared_ptr<Entity> addEntity(const std::string& tag);
    std::shared_ptr<Player> addPlayer(const std::string& tag);

    const EntityVec& getEntities() { return m_entities; }
    EntityVec getEntities(const std::string& tag) { return m_entityMap[tag]; }

};

#endif //ENTITYMANAGER_H

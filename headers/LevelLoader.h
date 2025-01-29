//
// Created by ionut on 11.01.2025.
//

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

////////// INCLUDE SECTION //////////
#include <string>
#include <memory>

#include "Assets.h"
#include "Player.h"

////////// DESCRIPTION //////////

/// Specialize class in loading a level map

////////// DEFINITION OF CLASS //////////
typedef std::vector<std::shared_ptr<Entity> > EntityVec;

class LevelLoader {

    static void setUpEntity(const std::shared_ptr<Entity> &object, std::ifstream &in, const sf::RenderWindow &rWindow);
public:
    explicit LevelLoader() = default;

    // this fill the entity vector, determine the maximum drawing level
    // and returns the player
    // so it have 3 functionalities
    static std::shared_ptr<Player> fill(EntityVec &vec, const std::string &fileName,
                                        sf::RenderWindow &rWindow);
};


#endif //LEVELLOADER_H

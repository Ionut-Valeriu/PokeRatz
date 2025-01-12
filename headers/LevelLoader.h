//
// Created by ionut on 11.01.2025.
//

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <string>
#include <memory>

#include "Assets.h"
#include "Player.h"

typedef std::vector<std::shared_ptr<Entity> > EntityVec;

class LevelLoader {
    Assets &m_assets;
public:
    explicit LevelLoader(Assets &assets);

    // this fill the entity vector, determine the maximum drawing level
    // and returns the player
    // so it have 3 functionalities
    std::shared_ptr<Player> fill(EntityVec &vec, const std::string &fileName,
                                        sf::RenderWindow &rWindow) const;
};


#endif //LEVELLOADER_H

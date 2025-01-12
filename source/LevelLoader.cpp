//
// Created by ionut on 11.01.2025.
//


#include <fstream>

#include "Exceptions.h"
#include "Background.h"
#include "Monster.h"
#include "Player.h"
#include "LevelLoader.h"

#include "Assets.h"
#include "EntityFactory.h"
#include "EntityManager.h"
#include "Game.h"

LevelLoader::LevelLoader(Assets &assets) : m_assets(assets) {
}

std::shared_ptr<Player> LevelLoader::fill(EntityVec &vec, const std::string &fileName,
                                          sf::RenderWindow &rWindow) const {
    std::ifstream in(fileName);
    if (!in.is_open()) { throw file_error{"File \"" + fileName + "\" not found"}; }

    std::shared_ptr<Player> player;
    char type;
    while (in >> type) {
        std::cout << "Current type: " << type << "\n";
        std::shared_ptr<Entity> object;
        object = EntityFactory::makeEntity(type, EntityManager::getEntityCount());

        switch (type) {
            // comments
            case '-': {
                std::string line;
                std::getline(in, line);
                continue;
            }
            // player
            case 'P': {
                player = std::dynamic_pointer_cast<Player>(object);
                break;
            }
            // default
            default: {
                if (object == nullptr) {
                    std::string line;
                    std::getline(in, line);
                    throw typing_error{"form LevelLoader:\tOn line: " + type + line + "\n"};
                }
            }
        }
        sf::Vector2f scale;
        sf::Vector2i rect, pos;
        std::string animation;
        bool solid;

        in >> animation >> scale.x >> scale.y >> rect.x >> rect.y >> pos.x >> pos.y >> solid;

        object->setAnimation(m_assets.getAnimation(animation));
        object->setPosition({
            object->getWidth() * static_cast<float>(pos.x) + object->getWidth() * static_cast<float>(rect.x) / 2.0f,
            static_cast<float>(rWindow.getSize().y) - object->getHeight() * static_cast<float>(pos.y) +
            object->getHeight() * static_cast<float>(rect.y) / 2.0f
        });
        object->setRect({0, 0, rect.x * 16, rect.y * 16});
        object->setScale(scale);
        object->setSolidity(solid);

        vec.push_back(object);
    }

    in.close();
    return player;
}

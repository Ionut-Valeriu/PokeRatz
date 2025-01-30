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
#include "Factory.h"
#include "EntityManager.h"
#include "Game.h"


void LevelLoader::setUpNonAnimation(const std::shared_ptr<Entity> &object, std::ifstream &in,
                                    const sf::RenderWindow &rWindow) {
    sf::Vector2f scale;
    sf::Vector2i rect, pos;
    bool solid;

    in >> scale.x >> scale.y >> rect.x >> rect.y >> pos.x >> pos.y >> solid;

    object->setPosition({
        object->getWidth() * static_cast<float>(pos.x) + object->getWidth() * static_cast<float>(rect.x) / 2.0f,
        static_cast<float>(rWindow.getSize().y) - object->getHeight() * static_cast<float>(pos.y) +
        object->getHeight() * static_cast<float>(rect.y) / 2.0f
    });
    object->setRect({0, 0, rect.x * 16, rect.y * 16});
    object->setScale(scale);
    object->setSolidity(solid);
}

void LevelLoader::setUpEntity(const std::shared_ptr<Entity> &object, std::ifstream &in,
                              const sf::RenderWindow &rWindow) {
    std::string animation;
    in >> animation;
    object->setAnimation(Assets::getAnimation(animation));
    setUpNonAnimation(object, in, rWindow);
}

std::shared_ptr<Player> LevelLoader::fill(EntityVec &vec, const std::string &fileName,
                                          sf::RenderWindow &rWindow) {
    std::ifstream in(fileName);
    if (!in.is_open()) { throw file_error{"File \"" + fileName + "\" not found"}; }

    std::shared_ptr<Player> player;
    char type;
    size_t drawLevel;
    while (in >> type) {
        switch (type) {
            // comments
            case '-': {
                std::string line;
                std::getline(in, line);
                continue;
            }
            // window
            case 'W': {
                int width, height, framerate;
                // r_read, g_read, b_read;
                // unsigned char r, g, b;
                bool fullscreen;

                in >> width >> height >> framerate >> fullscreen;
                // >> r_read >> g_read >> b_read;
                // r = r_read;
                // b = b_read;
                // g = g_read;

                rWindow.create(sf::VideoMode(width, height), "PokeRatz",
                               fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
                rWindow.setFramerateLimit(framerate);

                // m_bgColor = sf::Color{r, g, b};
                break;
            }

            // default for every entity
            default: {
                in >> drawLevel;
                std::shared_ptr<Entity> object = Factory<Entity>::makeEntity(
                    type, EntityManager::getEntityCount(), drawLevel);
                if (object == nullptr) {
                    std::string line;
                    std::getline(in, line);
                    throw typing_error{"form LevelLoader:\tOn line: " + std::to_string(type) + line + "\n"};
                }
                if (type == 'P') player = std::dynamic_pointer_cast<Player>(object);
                setUpEntity(object, in, rWindow);
                vec.push_back(object);
            }
        }
    }

    in.close();
    return player;
}

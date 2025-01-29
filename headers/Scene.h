//
// Created by ionut on 28.01.2025.
//

#ifndef SCENE_H
#define SCENE_H

////////// INCLUDE SECTION //////////
#include "EntityManager.h"
// #include "Game.h"
#include "Player.h"

////////// DESCRIPTION //////////

/// using the STATE DESIGN PATTERN
/// this serve the purpose of separating the game
/// into its specific states

////////// SHORTCUTS //////////
typedef std::map<sf::Keyboard::Key, std::pair<ActionName, Direction> > ActionMap;

////////// DEFINITION OF CLASS //////////
class Scene {
protected:
    // size 104
    EntityManager m_entities;

    // size 48
    ActionMap m_actions;

    // size 16
    std::shared_ptr<Player> m_player;
    // std::shared_ptr<Game> m_game;

    // size 8
    size_t m_currentFrame = 0;

    // size 1
    bool m_paused = false;

    // scene play related
    void registerAction(sf::Keyboard::Key inputKey, const ActionName &aName, const Direction dir = Direction::NONE);

public:
    virtual ~Scene() = default;

    Scene(const std::string &file, sf::RenderWindow &window);

    virtual void update() = 0;

    virtual bool sDoActions(ActionType, sf::Keyboard::Key) = 0;
};


#endif //SCENE_H

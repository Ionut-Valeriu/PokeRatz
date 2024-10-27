//
// Created by ionut on 22.10.2024.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Actions.h"
#include "EntityManager.h"

typedef std::map<int, std::string> ActionMap;

class Game {

    bool m_running = true;
    bool m_paused = false;
    size_t currentFrame = 0;

    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_text;
    std::shared_ptr<Player> m_player;
    EntityManager m_entityManager;
    ActionMap m_actions;

    void init(const std::string& path);

    void sRender();

    void sMovement();

    void sDoActions(Actions &action);

    void sUserInput();

    const ActionMap& getActionMap() const;

    // scene play related
    void registerAction (int inputKey, const std::string& actionName);

public:

    Game(const std::string& path);
    void run();
};



#endif //GAME_H

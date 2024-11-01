//
// Created by ionut on 22.10.2024.
//

#ifndef GAME_H
#define GAME_H

////////// INCLUDE SECTION //////////
#include <SFML/Graphics.hpp>

#include "Actions.h"
#include "EntityManager.h"

////////// DESCRIPTION //////////

/// todo - separate in 2 classes
/// this class is a temporary class that functions
/// like 2 different ones: GameEngine and Scene
/// lots of the functionality were based on entity components that were public
/// so this class just iterates through entities and call specific functions
///
/// this class manage the system events:
/// - initialization
/// --1 loading config files
/// --1 --1 initializing window
/// --1 --2 initializing font
/// --2 setting up the action map (this will be moved on the scene class)
/// - hande user input (raw)
/// - movement & actions
/// - rendering
/// - collision / intersecting (soon implemented)
/// - lifespan (not implemented)

////////// SHORTCUTS //////////
typedef std::map<int, std::string> ActionMap;

////////// DEFINITION OF CLASS //////////
class Game {

    bool m_running = true;
    bool m_paused = false;
    size_t currentFrame = 0;

    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_text;
    std::shared_ptr<Player> m_player; // this might be temporary (can be implemented on scene
    EntityManager m_entityManager;
    ActionMap m_actions; // this will be implemented o  scene

    void init(const std::string& path);

    void sRender();

    void sMovement();

    void sDoActions(const Actions &action);

    void sUserInput();

    const ActionMap& getActionMap() const;

    // scene play related
    void registerAction (int inputKey, const std::string& actionName);

    void onEnd();

public:
    explicit Game(const std::string& path);
    void run();
};



#endif //GAME_H

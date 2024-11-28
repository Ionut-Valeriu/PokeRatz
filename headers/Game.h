//
// Created by ionut on 22.10.2024.
//

#ifndef GAME_H
#define GAME_H

////////// INCLUDE SECTION //////////
#include <SFML/Graphics.hpp>

#include "Actions.h"
#include "Assets.h"
#include "EntityManager.h"

////////// DESCRIPTION //////////

/// todo - separate in 2 classes
/// this class is a temporary class that functions
/// like 2 different ones: GameEngine and Scene
/// lots of the functionality were based on entity components that were public
/// so this class just iterates through entities and call specific functions
///
/// convention: methods that start with "s" are assigned to the "system"
/// this is implemented to separate game and scene methods from the rest
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
    // size 536
    sf::RenderWindow m_window;

    // size 368
    sf::Text m_text;

    // size 168
    sf::View m_view{{200.0f, 200.0f}, {1024.0f, 576.0f}};

    // size 152
    sf::Font m_font;

    // size 144
    Assets m_assets;

    // size 104
    EntityManager m_entityManager;

    // size 48
    ActionMap m_actions; // this will be implemented o  scene

    // size 24
    sf::Sound m_sound;

    // size 16
    std::shared_ptr<Player> m_player; // this might be temporary (can be implemented on scene)

    // size 8
    size_t currentFrame = 0;

    // size 4
    sf::Color m_bgColor;

    // size 1
    bool m_running = true;
    bool m_paused = false;


    void init(const std::string& path);

    void sRender();

    void sMovement();

    void sDoActions(const Actions &action);

    void sUserInput();

    void sAnimation();

    const ActionMap& getActionMap() const;

    // scene play related
    void registerAction (int inputKey, const std::string& actionName);

    void onEnd();

    // void sLvlBuilder(std::string path);

public:
    explicit Game(const std::string& path);
    void run();


};



#endif //GAME_H

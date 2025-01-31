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
#include "Factory.h"
#include "Player.h"
#include "Scene.h"

////////// DESCRIPTION //////////

/// todo - separate in 2 classes
/// this class is a temporary class that functionsclass Game
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
typedef std::map<std::string, std::shared_ptr<Scene> > SceneMap;
typedef std::map<std::string, std::pair<char, std::string> > SceneSettings;

////////// DEFINITION OF CLASS //////////
class Game {
    // size 536
    sf::RenderWindow m_window;

    // size 368
    sf::Text m_text;

    // size 168
    sf::View m_view;

    // size 152
    sf::Font m_font;

    // size 48
    SceneMap m_scenes;
    SceneSettings m_sceneSettings;

    // size 24
    sf::Sound m_sound;

    // size 16
    std::shared_ptr<Scene> m_currentScene;

    // size 4
    sf::Color m_bgColor; // todo mark

    // size 1
    bool m_running = true;

    std::string m_sceneName;

    void init(const std::string &path);

    void sUserInput();

    void addScene(const std::string &name, char type, const std::string &file);

    void changeScene(SceneManager name);

    void update();

public:
    explicit Game(const std::string &path);

    void onEnd();

    void run();
};


#endif //GAME_H

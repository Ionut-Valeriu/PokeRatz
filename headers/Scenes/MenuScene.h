//
// Created by ionut on 28.01.2025.
//

#ifndef MENUSCENE_H
#define MENUSCENE_H

////////// INCLUDE SECTION //////////
#include "Scene.h"

////////// DESCRIPTION //////////

/// using the STATE DESIGN PATTERN
/// this class is for the scenes that are menu related
/// like the start of the game

////////// DEFINITION OF CLASS //////////
class MenuScene : public Scene {
    sf::Text text{"PRESS ENTER TO PLAY", Assets::getFont("Arial")};

    void sRender();

    void init();

public:
    SceneManager getNext() override;

    bool sDoActions(ActionType, sf::Keyboard::Key) override;

    MenuScene(const std::string &file, sf::RenderWindow &window);

    void update() override;
};


#endif //MENUSCENE_H

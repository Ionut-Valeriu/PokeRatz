//
// Created by ionut on 28.01.2025.
//

#ifndef PLAYSCENE_H
#define PLAYSCENE_H

////////// INCLUDE SECTION //////////
#include "Scene.h"

////////// DESCRIPTION //////////

/// todo

////////// DEFINITION OF CLASS //////////
class PlayScene : public Scene {
    sf::RenderWindow &m_window;

    sf::View m_view{{0, 0, 1920, 1080}};

    bool m_drawSprites = true;
    bool m_drawOutline = false;
    bool m_drawOrigin = false;

    void init();

    void sCollision();

    void sMovement();

    void sAnimation() const;

    void sRender();

public:
    PlayScene(const std::string &levelPath, sf::RenderWindow &window);

    bool sDoActions(ActionType, sf::Keyboard::Key) override;

    void update() override;
};


#endif //PLAYSCENE_H

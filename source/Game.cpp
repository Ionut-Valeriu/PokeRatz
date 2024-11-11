//
// Created by ionut on 22.10.2024.
//

#include "Game.h"

#include <fstream>
#include <future>
#include <iostream>
#include <string>

#include "Actions.h"
#include "Enums.h"

void Game::init(const std::string &path) {

    // initialization controls
    registerAction(sf::Keyboard::Escape, "CLOSE");
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::E, "INTERACT");

    std::ifstream in { path };
    std::string keyword;

    while(in >> keyword) {
        if (keyword == "Window") {
            int width, height, framerate, r_read, g_read, b_read;
            unsigned char r, g, b;
            bool fullscreen;

            in >> width >> height >> framerate >> fullscreen >> r_read >> g_read >> b_read;
            r = r_read; b = b_read; g = g_read;

            m_window.create(sf::VideoMode(width, height), "PokeRatz", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
            m_window.setFramerateLimit(framerate);

            m_bgColor = sf::Color{r, g, b};
        }
        else if (keyword == "Assets") {
            std::string assetsPath;
            in >> assetsPath;
            m_assets.loadFromFile(assetsPath);
        }
    }

    in.close();
    std::cout << "\nInit finished!\n" << m_assets << "\n";

    // todo - remove - only for cppcherck

    std::string testAnimName = "Stand";

    Animation animationTest;//{testAnimName, m_assets.getTexture("TexPlayer")};

    animationTest = m_assets.getAnimation(testAnimName);
    animationTest.getSprite();
    animationTest.getName();
    m_assets.getTextureMap();
    m_assets.getAnimationMap();

    m_player = m_entityManager.addPlayer("player", m_assets.getTexture("TexPlayer"));
    auto test = m_entityManager.addEntity("test", m_assets.getTexture("TexPlayer"));
    auto test2 = m_entityManager.addEntity("test", m_assets.getTexture("TexPlayer"));
    if (test->collide(*test2)) {
        std::cout << "initial collision\n";
    } else {
        std::cout << "NOT collision\n";
    }
    std::cout << *m_player << "\n\n" << *test << "\n\n" << *test2 << "\n";

    test->remove();
    // test2->remove();
    //

    m_font = m_assets.getFont("Arial");
}

void Game::run() {
    while (m_running) {

        m_entityManager.update();

        sUserInput();

        if(!m_paused) {
            sMovement();
        }

        sRender();

        if (!m_paused) {
            currentFrame++;
            m_player->incFrame();
        }
    }
}

void Game::sDoActions(const Actions& action) {

    if (action.type() == "START") {
             if (action.name() == "CLOSE") { onEnd(); }
        else if (action.name() == "PAUSE") { m_paused = true; }
        else if (action.name() == "UP"   ) { m_player->setUp(true); }
        else if (action.name() == "DOWN" ) { m_player->setDown(true); }
        else if (action.name() == "LEFT" ) { m_player->setLeft(true); }
        else if (action.name() == "RIGHT") { m_player->setRight(true); }
    }
    else if (action.type() == "END") {
             if (action.name() == "PAUSE") { m_paused = false; }
        else if (action.name() == "UP"   ) { m_player->setUp(false); }
        else if (action.name() == "DOWN" ) { m_player->setDown(false); }
        else if (action.name() == "LEFT" ) { m_player->setLeft(false); }
        else if (action.name() == "RIGHT") { m_player->setRight(false); }
    }
}

void Game::sUserInput() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            // if the current scene does not have an action associated with this key, skip the event
            if (getActionMap().find(event.key.code) == getActionMap().end()) { continue; }

            // determine start or end action by whether it was key pres or release
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            // look up the action and send the action to the scene
            sDoActions( Actions {getActionMap().at(event.key.code), actionType} );
        }
    }
}

void Game::sRender() {
    m_window.clear(m_bgColor);
    for (const std::shared_ptr<Entity> &e: m_entityManager.getEntities()) {
        e->draw(m_window);
    }
    m_window.display();
}

void Game::sMovement() {
    Move x = Move::STAY;
    Move y = Move::STAY;

    if (m_player->up()) {
        if (m_player->getY() > 0)
        { y = Move::REVERSE; }
    }
    else if (m_player->down()) {
        if(m_player->getY()+m_player->getHeight()+m_player->speed() < m_window.getSize().y)
        { y = Move::GO; }
    }
    else if (m_player->left()) {
        if(m_player->getX() > 0)
        { x = Move::REVERSE; }
    }
    else if (m_player->right()) {
        if(m_player->getX()+m_player->getWidth()+m_player->speed() < m_window.getSize().x) {
            x = Move::GO;
        }
    }

    m_player->setVelocity(x, y);

    for (const auto &e : m_entityManager.getEntities()) {
        e->updatePos();
    }
}

const ActionMap & Game::getActionMap() const {
    return m_actions;
}

void Game::registerAction(int inputKey, const std::string &actionName) {
    m_actions.insert(std::pair<int, std::string>(inputKey, actionName));
}

void Game::onEnd() {
    m_running = false;
}

Game::Game(const std::string &path) {
    init(path);
}

//
// Created by ionut on 22.10.2024.
//

#include "Game.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Actions.h"
#include "Enums.h"

void Game::run() {
    while (m_running) {

        m_entityManager.update();

        sUserInput();

        if(!m_paused) {
            sMovement();
        }

        sRender();

        if (!m_paused) currentFrame++;
    }
}

void Game::init(const std::string &path) {

    // initialization controls
    registerAction(sf::Keyboard::Escape, "CLOSE");
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::E, "INTERACT");

    // todo - remove - only for cppcherck
    m_player = m_entityManager.addPlayer("player");
    auto test = m_entityManager.addEntity("test");
    auto test2 = m_entityManager.addEntity("test");
    test->collide(*test2);

    /// todo
    /// temp

    std::ifstream in { path };
    std::string keyword;

    while(in >> keyword) {
        if (keyword == "Window") {
            int width, height, framerate;
            bool fullscreen;

            in >> width >> height >> framerate >> fullscreen;

            m_window.create(sf::VideoMode(width, height), "PokeRatz", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
            m_window.setFramerateLimit(framerate);
        }
        else if (keyword == "Font") {
            std::string fontPath;
            in >> fontPath;
            if(!m_font.loadFromFile(fontPath)) {
                std::cerr<<"Failed to load font file: "<<fontPath<<std::endl;
                exit(1);
            }
        }
    }

    std::cout << "Init finished!\n";
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
    m_window.clear();
    for (const std::shared_ptr<Entity> &e: m_entityManager.getEntities()) {
        e->draw(m_window);
    }
    m_window.display();
}

void Game::sMovement() {
    Move x = STAY;
    Move y = STAY;

    if (m_player->up()) { y = REVERSE; }
    if (m_player->down()) { y = GO; }
    if (m_player->left()) { x = REVERSE; }
    if (m_player->right()) { x = GO; }

    m_player->setVelocity(x, y);

    for (auto&e : m_entityManager.getEntities()) {
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

//
// Created by ionut on 22.10.2024.
//

#include "Game.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Actions.h"

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

    m_player = m_entityManager.addPlayer("player");
    auto test_e = m_entityManager.addEntity("test-entity");

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

void Game::sDoActions(Actions& action) {
    if(action.name() == "CLOSE") { onEnd();}
    else if (action.name() == "PAUSE") { m_paused = true; }
    else { m_player->setAction(action); }
}

void Game::sUserInput() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            // if the current scene does not have an action associated with this key, skip the event
            if (getActionMap().find(event.key.code) == getActionMap().end()) { continue; }

            // determine start or end action by whether it was key pres or release
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            // look up the action and send the action to the scene

            Actions a(getActionMap().at(event.key.code), actionType);
            sDoActions(a);
        }
    }
}

void Game::sRender() {
    m_window.clear();

    for (auto &e : m_entityManager.getEntities()) {
        e->draw(m_window);
    }

    m_window.display();
}

void Game::sMovement() {

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

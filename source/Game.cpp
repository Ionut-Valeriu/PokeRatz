//
// Created by ionut on 22.10.2024.
//

#include "../headers/Game.h"

#include <fstream>
#include <future>
#include <iostream>
#include <string>

#include "Actions.h"
#include "Enums.h"
#include "Assets.h"
#include "Background.h"
#include "Entity.h"
#include "Monster.h"
#include "Player.h"
#include "Exceptions.h"

void Game::init(const std::string &path) {
    // initialization controls
    registerAction(sf::Keyboard::Escape, "CLOSE");
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::E, "INTERACT");
    registerAction(sf::Keyboard::Num1, "SPRITES");
    registerAction(sf::Keyboard::Num2, "SHAPES");
    registerAction(sf::Keyboard::Num3, "ORIGIN");

    // loading assets and settings
    std::ifstream in{path};

    try {
        std::string keyword;
        while (in >> keyword) {
            if (keyword[0] == '-') {
                std::getline(in, keyword);
                continue;
            }
            if (keyword == "Window") {
                int width, height, framerate, r_read, g_read, b_read;
                unsigned char r, g, b;
                bool fullscreen;

                in >> width >> height >> framerate >> fullscreen >> r_read >> g_read >> b_read;
                r = r_read;
                b = b_read;
                g = g_read;

                m_window.create(sf::VideoMode(width, height), "PokeRatz",
                                fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
                m_window.setFramerateLimit(framerate);

                m_bgColor = sf::Color{r, g, b};
            } else if (keyword == "Assets") {
                std::string assetsPath;
                in >> assetsPath;
                Assets::loadFromFile(assetsPath);
            } else if (keyword == "Level") {
                std::string levelPath;
                in >> levelPath;
                LevelLoader loader;
                std::cout << "loader build successful\n";
                m_player = m_entityManager.load(levelPath, loader, m_window);
                std::cout << "Level loaded!\n";
            } else if (keyword == "View") {
                float width, height;
                in >> width >> height;
                m_view.reset({0.0f, 0.0f, width, height});
            } else if (keyword == "Sound") {
                std::string musicName;
                bool looping;
                in >> musicName >> looping;
                std::cout << musicName << "\n";
                m_sound = Assets::getSound(musicName);
                m_sound.setLoop(looping);
            } else {
                throw typing_error(keyword);
            }
        }
    } catch (const file_error &e) {
        std::cerr << "File error:\n\t" << e.what();
        // throw standard_error(e.what());
    } catch (const typing_error &e) {
        std::cerr << "Typing error:\n\t" << e.what();
        // throw standard_error(e.what());
    } catch (const loading_error &e) {
        std::cerr << "Loading error:\n\t" << e.what();
        // throw standard_error(e.what());
    } catch (const standard_error &e) {
        std::cerr << "Exit because of:\n\t" << e.what();
        exit(1);
    }

    in.close();
    std::cout << "\nInit finished!\n" << Assets() << "\n";

    // todo - remove - only for cppcheck
    m_font = Assets::getFont("Arial");
    //

    m_sound.play();
}

void Game::run() {
    while (m_running) {
        m_entityManager.update();

        sUserInput();
        if (!m_paused) {
            sMovement();
            sCollision();
            sAnimation();
        }
        sRender();

        if (!m_paused) {
            currentFrame++;
            m_player->incFrame();
        }
    }
}

void Game::sDoActions(const Actions &action) {
    if (action.type() == "START") {
        if (action.name() == "UP") { m_player->setUp(true); } else if (
            action.name() == "DOWN") { m_player->setDown(true); } else if (
            action.name() == "LEFT") { m_player->setLeft(true); } else if (
            action.name() == "RIGHT") { m_player->setRight(true); } else if (
            action.name() == "SPRITES") { m_drawSprites = !m_drawSprites; } else if (
            action.name() == "SHAPES") { m_drawOutline = !m_drawOutline; } else if (
            action.name() == "ORIGIN") { m_drawOrigin = !m_drawOrigin; } else if (
            action.name() == "PAUSE") { m_paused = !m_paused; } else if (
            action.name() == "CLOSE") { onEnd(); }
    } else if (action.type() == "END") {
        if (action.name() == "UP") { m_player->setUp(false); } else if (
            action.name() == "DOWN") { m_player->setDown(false); } else if (
            action.name() == "LEFT") { m_player->setLeft(false); } else if (
            action.name() == "RIGHT") { m_player->setRight(false); }
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
            if (!getActionMap().contains(event.key.code)) { continue; }

            // determine start or end action by whether it was key pres or release
            const std::string actionType = event.type == sf::Event::KeyPressed ? "START" : "END";

            // look up the action and send the action to the scene
            sDoActions({getActionMap().at(event.key.code), actionType});
        }
    }
}

void Game::sAnimation() const {
    std::string animationName;

    switch (m_player->state()) {
        case State::UP:
            animationName = "PUp";
            break;

        case State::DOWN:
        case State::STAND:
            animationName = "PStand";
            break;

        case State::LEFT:
            animationName = "PSide";
            m_player->setLeft();
            break;

        case State::RIGHT:
            animationName = "PSide";
            m_player->setRight();
            break;
    }

    if (m_player->getAnimation()->getName() != animationName) {
        m_player->setAnimation(Assets::getAnimation(animationName));
    }
    m_player->getAnimation()->setScale(m_player->getScale());

    m_player->updateAnimation();

    // todo - all E
}

void Game::sCollision() {
    auto vec = m_entityManager.getEntities();
    for (auto e1 = vec.begin(); e1 + 1 != vec.end(); ++e1) {
        for (auto e2 = e1 + 1; e2 != vec.end(); ++e2) {
            if ((*e1)->collide(**e2)) {
                (*e1)->onCollide((*e2)->isSolid());
                (*e2)->onCollide((*e1)->isSolid());

                auto m1 = std::dynamic_pointer_cast<Monster>(*e1);
                auto m2 = std::dynamic_pointer_cast<Monster>(*e2);

                auto p1 = std::dynamic_pointer_cast<Player>(*e1);
                auto p2 = std::dynamic_pointer_cast<Player>(*e2);

                if ((m1 != nullptr && p2 != nullptr) || (m2 != nullptr && p1 != nullptr)) {
                    std::cout << "You win\n";
                    onEnd();
                }
            }
        }
    }
}

void Game::sRender() {
    m_window.clear(m_bgColor);
    m_view.setCenter(m_player->getX(), m_player->getY());
    m_window.setView(m_view);

    for (size_t i = 1; i <= m_entityManager.getMaxDrawLevel(); i++) {
        for (const std::shared_ptr<Entity> &e: m_entityManager.getEntitiesOnLevel(i)) {
            e->draw(m_window, m_drawSprites, m_drawOutline, m_drawOrigin);
        }
    }

    m_window.display();
}

void Game::sMovement() {
    for (const auto &e: m_entityManager.getEntities()) {
        e->updatePos();
    }
}

void Game::registerAction(int inputKey, const std::string &actionName) {
    m_actions.insert({inputKey, actionName});
}

void Game::onEnd() { m_running = false; }

Game::Game(const std::string &path) { init(path); }

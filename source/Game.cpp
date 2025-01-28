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

void Game::registerAction(int inputKey, const ActionName &aName, const Direction dir = Direction::NONE) {
    m_actions.insert({inputKey, {aName, dir}});
}

void Game::init(const std::string &path) {
    // initialization controls
    // registerAction(sf::Keyboard::E, ActionName::INTERACT);
    registerAction(sf::Keyboard::Escape, ActionName::CLOSE);
    registerAction(sf::Keyboard::P, ActionName::PAUSE);
    registerAction(sf::Keyboard::Num1, ActionName::SPRITES);
    registerAction(sf::Keyboard::Num2, ActionName::SHAPES);
    registerAction(sf::Keyboard::Num3, ActionName::ORIGIN);
    // movements
    registerAction(sf::Keyboard::W, ActionName::MOVE, Direction::UP);
    registerAction(sf::Keyboard::S, ActionName::MOVE, Direction::DOWN);
    registerAction(sf::Keyboard::A, ActionName::MOVE, Direction::LEFT);
    registerAction(sf::Keyboard::D, ActionName::MOVE, Direction::RIGHT);

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
    switch (action.name()) {
        // basic movement
        case ActionName::MOVE: {
            m_player->setDirection(action);
            break;
        }
        // toggle pause
        case ActionName::PAUSE: {
            if (action.type() == ActionType::START)
                m_paused = !m_paused;
            break;
        }
        // toggle the visibility of textures / bounding box / origin of every entity
        case ActionName::SPRITES: {
            if (action.type() == ActionType::START)
                m_drawSprites = !m_drawSprites;
            break;
        }
        case ActionName::SHAPES: {
            if (action.type() == ActionType::START)
                m_drawOutline = !m_drawOutline;
            break;
        }
        case ActionName::ORIGIN: {
            if (action.type() == ActionType::START)
                m_drawOrigin = !m_drawOrigin;
            break;
        }
        // close the game
        case ActionName::CLOSE: {
            if (action.type() == ActionType::END)
                onEnd();
            break;
        }
        // default: throw;
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
            auto type = event.type == sf::Event::KeyPressed ? ActionType::START : ActionType::END;

            // look up the action and send the action to the scene
            sDoActions({type, getActionMap().at(event.key.code)});
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


void Game::onEnd() { m_running = false; }

Game::Game(const std::string &path) { init(path); }

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
    std::string keyword;

    while (in >> keyword) {
        if (keyword == "--") {
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
            m_assets.loadFromFile(assetsPath);
        } else if (keyword == "Level") {
            std::string levelPath;
            in >> levelPath;
            levelLoader(levelPath);
        } else {
            std::cerr << "Error: " << keyword << " does not match any configuration keyword.\n";
            exit(1);
        }
    }

    in.close();
    std::cout << "\nInit finished!\n" << m_assets << "\n";

    // todo - remove - only for cppcheck
    m_font = m_assets.getFont("Arial");
    //


    m_sound.play();
}

void Game::levelLoader(const std::string &path) {
    std::cout << "Loading level " << path << "\n";

    std::ifstream in(path);
    char type;

    while (in >> type) {


        std::shared_ptr<Entity> block;

        // The cases are ordered by frequency of occurrence,
        // from the most frequent to the least frequent.
        switch (type) {
            // background
            case 'B':
                block = m_entityManager.addEntity<Background>(1);
                break;
            // monster
            case 'M':
                block = m_entityManager.addEntity<Monster>(2);
                break;
            // player
            case 'P':
                m_player = m_entityManager.addEntity<Player>(3);
                block = m_player;
                break;
            // comments
            case '-': {
                std::string rest;
                std::getline(in, rest);
                continue;
            }
            // sound
            case 'S': {
                std::string musicName;
                bool looping;
                in >> musicName >> looping;
                std::cout << musicName << "\n";
                m_sound = m_assets.getSound(musicName);
                m_sound.setLoop(looping);
                continue;
            }
            // view
            case 'V': {
                float W, H;
                in >> W >> H;
                m_view.reset({0, 0, W, H});
                continue;
            }
            default:
                std::cerr << "Unrecognized character: " << type << "in the level loader\n";
                exit(1);
        }

        std::cout << type << "\n";;

        sf::Vector2f scale;
        sf::Vector2i rect, pos;
        std::string animation;
        bool solid;

        in >> animation >> scale.x >> scale.y >> rect.x >> rect.y >> pos.x >> pos.y >> solid;

        // block->init();
        block->setAnimation(m_assets.getAnimation(animation));
        block->setPosition({
            block->getWidth() * static_cast<float>(pos.x) + block->getWidth() * rect.x / 2,
            static_cast<float>(m_window.getSize().y) - block->getHeight() * static_cast<float>(pos.y) +
            block->getHeight() * rect.y / 2
        });
        block->setRect({0, 0, rect.x * 16, rect.y * 16});
        block->setScale(scale);
        block->setSolidity(solid);
    }
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
            action.name() == "ORIGIN") { m_drawOrigin = !m_drawOrigin; } else if (action.name() == "PAUSE") {
            m_paused = !m_paused;
        } else if (action.name() == "CLOSE") { onEnd(); }
    } else if (action.type() == "END") {
        if (action.name() == "UP") { m_player->setUp(false); } else if (
            action.name() == "DOWN") { m_player->setDown(false); } else if (action.name() == "LEFT") {
            m_player->setLeft(false);
        } else if (action.name() == "RIGHT") { m_player->setRight(false); }
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

void Game::sAnimation() {
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
            m_player->setScale({-5.0f, 5.0f});
            break;

        case State::RIGHT:
            animationName = "PSide";
            m_player->setScale({5.0f, 5.0f});
            break;
    }

    m_player->getAnimation()->setScale(m_player->getScale());
    if (m_player->getAnimation()->getName() != animationName) {
        m_player->setAnimation(m_assets.getAnimation(animationName));
    }

    // Animation a = m_assets.getAnimation("PStand");
    // a.update();
    m_player->updateAnimation();

    // todo - all E
}

void Game::sCollision() {
    auto vec = m_entityManager.getEntities();
    for (auto e1 = vec.begin(); e1 + 1 != vec.end(); e1++) {
        for (auto e2 = e1 + 1; e2 != vec.end(); e2++) {
            if ((*e1)->collide(**e2)) {
                (*e1)->onCollide((*e2)->isSolid());
                (*e2)->onCollide((*e1)->isSolid());
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
    auto x = Move::STAY;
    auto y = Move::STAY;

    if (m_player->up()) {
        m_player->setState(State::UP);
        y = Move::REVERSE;
    } else if (m_player->down()) {
        m_player->setState(State::DOWN);
        y = Move::GO;
    } else if (m_player->left()) {
        m_player->setState(State::LEFT);
        x = Move::REVERSE;
    } else if (m_player->right()) {
        m_player->setState(State::RIGHT);
        x = Move::GO;
    }

    if (x == Move::STAY && y == Move::STAY) {
        m_player->setState(State::STAND);
    }
    m_player->setVelocity(x, y);

    for (const auto &e: m_entityManager.getEntities()) {
        e->updatePos();
    }
}

void Game::registerAction(int inputKey, const std::string &actionName) {
    m_actions.insert({inputKey, actionName});
}

void Game::onEnd() { m_running = false; }

Game::Game(const std::string &path) { init(path); }

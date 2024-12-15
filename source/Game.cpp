//
// Created by ionut on 22.10.2024.
//

#include "../headers/Game.h"

#include <fstream>
#include <future>
#include <iostream>
#include <string>

#include "../headers/Actions.h"
#include "../headers/Enums.h"
#include "../headers/Assets.h"

void Game::init(const std::string &path) {

    // initialization controls
    registerAction(sf::Keyboard::Escape, "CLOSE");
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::E, "INTERACT");

    // loading assets and settings
    std::ifstream in { path };
    std::string keyword;

    while(in >> keyword) {
        if (keyword == "--") {
            std::getline(in, keyword);
            continue;
        }
        if (keyword == "Window") {
            int width, height, framerate, r_read, g_read, b_read;
            unsigned char r, g, b;
            bool fullscreen;

            in >> width >> height >> framerate >> fullscreen >> r_read >> g_read >> b_read;
            r = r_read; b = b_read; g = g_read;

            m_window.create(sf::VideoMode(width, height), "PokeRatz", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
            m_window.setFramerateLimit(framerate);

            m_bgColor = sf::Color{r, g, b};
        } else if (keyword == "Assets") {
            std::string assetsPath;
            in >> assetsPath;
            m_assets.loadFromFile(assetsPath);
        } else if (keyword == "Level") {
            std::string levelPath;
            in >> levelPath;
            levelLoader("resources/config/MainMap.txt");
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
    std::ifstream in (path);
    std::string keyword;

    while (in >> keyword) {
        if (keyword == "--") {
            std::getline(in, keyword);
            continue;
        }

        std::cout << "Loading " << keyword << "\n";

        if (keyword == "Player") {
            std::string defAnim;
            float X, Y;
            size_t dL;

            in >> defAnim >> dL >> X >> Y;

            m_player = m_entityManager.addPlayer("player", dL);
            m_player->setAnimation(m_assets.getAnimation(defAnim));
            m_player->setPosition({m_player->getWidth() * X + m_player->getWidth()/2,
                              static_cast<float>(m_window.getSize().y) - m_player->getHeight()*Y - m_player->getHeight()/2});

            continue;
        }
        if (keyword == "View") {
            float W, H;
            in >> W >> H;
            m_view.reset({0, 0, W, H});
            continue;
        }
        if (keyword == "Sound") {
            std::string musicName;
            bool looping;
            in >> musicName >> looping;
            m_sound = m_assets.getSound(musicName);
            m_sound.setLoop(looping);
            continue;
        }

        // else choose an animation for a non-moving entity

        sf::Vector2i scale, rect, pos;
        in >> scale.x >> scale.y >> rect.x >> rect.y >> pos.x >> pos.y;

        auto block = m_entityManager.addEntity(keyword);
        block->setAnimation(m_assets.getAnimation(keyword));
        block->setPosition({block->getWidth()*static_cast<float>(pos.x) + block->getWidth()/2,
                              static_cast<float>(m_window.getSize().y) - block->getHeight()*static_cast<float>(pos.y) - block->getHeight()/2});

        block->getAnimation()->setRect(sf::IntRect{0, 0, rect.x * 16, rect.y * 16});
        block->setBorderT(0);
    }
}

void Game::run() {
    while (m_running) {

        m_entityManager.update();

        sUserInput();

        if(!m_paused) {
            sMovement();
            sAnimation();
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
        if      (action.name() == "CLOSE") { onEnd(); }
        else if (action.name() == "PAUSE") { m_paused = true; }
        else if (action.name() == "UP"   ) { m_player->setUp(true); }
        else if (action.name() == "DOWN" ) { m_player->setDown(true); }
        else if (action.name() == "LEFT" ) { m_player->setLeft(true); }
        else if (action.name() == "RIGHT") { m_player->setRight(true); }
    }
    else if (action.type() == "END") {
        if      (action.name() == "PAUSE") { m_paused = false; }
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
            if (!getActionMap().contains(event.key.code)) { continue; }

            // determine start or end action by whether it was key pres or release
            const std::string actionType = event.type == sf::Event::KeyPressed ? "START" : "END";

            // look up the action and send the action to the scene
            sDoActions( Actions {getActionMap().at(event.key.code), actionType} );
        }
    }
}

void Game::sAnimation()  {
    std::string animationName;

    switch (m_player->state()) {
        case State::UP:
            animationName = "PUp";
        break;

        case State::DOWN:   case State::STAND:
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

void Game::sRender() {
    m_window.clear(m_bgColor);
    m_view.setCenter(m_player->getX(), m_player->getY());
    m_window.setView(m_view);

    for (size_t i = 1; i <= m_entityManager.getMaxDrawLevel(); i++ ) {
        for (const std::shared_ptr<Entity> &e: m_entityManager.getEntitiesOnLevel(i)) {
            e->draw(m_window);
        }
    }

    m_window.display();
}

void Game::sMovement() {
    auto x = Move::STAY;
    auto y = Move::STAY;

    if (m_player->up()) {
        if (m_player->getY() > m_player->getHeight()/2 + 80.0f) {
            m_player->setState(State::UP);
            y = Move::REVERSE;
        }
    }
    else if (m_player->down()) {
        if(m_player->getY()+m_player->getHeight()/2+m_player->speed()
            < static_cast<float>(m_window.getSize().y) * 2.0f + 40.0f)
        {
            m_player->setState(State::DOWN);
            y = Move::GO;
        }
    }
    else if (m_player->left()) {
        if(m_player->getX() > m_player->getWidth()/2 + 80.0f) {
            m_player->setState(State::LEFT);
            x = Move::REVERSE;
        }
    }
    else if (m_player->right()) {
        if(m_player->getX()+m_player->getWidth()/2+m_player->speed()
            < static_cast<float>(m_window.getSize().x) - 40.0f)
        {
            m_player->setState(State::RIGHT);
            x = Move::GO;
        }
    }

    if (x == Move::STAY && y == Move::STAY) {
        m_player->setState(State::STAND);
    }

    m_player->setVelocity(x, y);

    // todo - for all e
    for (const auto &e : m_entityManager.getEntities("player")) {
        e->updatePos();
    }
    for (const auto &e : m_entityManager.getEntities("test")) {
        if (m_player->collide(*e)) {
            e->remove();
        }
    }
}

const ActionMap & Game::getActionMap() const {
    return m_actions;
}

void Game::registerAction(int inputKey, const std::string &actionName) {
    m_actions.insert({inputKey, actionName});
}

void Game::onEnd() {
    m_running = false;
}

Game::Game(const std::string &path) {
    init(path);
}

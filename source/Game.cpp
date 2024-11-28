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

    // todo - move & from file
    // map creation
    for (unsigned int j = 1; j < m_window.getSize().y / 40 ; j++) {
        for (unsigned int i = 1; i < m_window.getSize().x / 80 - 1 ; i++) {
            auto e = m_entityManager.addEntity("Grass");
            e->setAnimation(m_assets.getAnimation("Grass"));
            e->setPosition({static_cast<float>(i) * 80.0f + 40.0f, static_cast<float>(j)*80.0f + 40.0f});
            e->setBorderT(0);
        }
    }

    // left
    for (unsigned int j = 0; j < m_window.getSize().y / 80 ; j++) {
            auto e = m_entityManager.addEntity("Block");
            e->setAnimation(m_assets.getAnimation("Block"));
            e->setPosition({40.0f, static_cast<float>(j)*80.0f + 40.0f});
            e->setBorderT(0);
    }

    // right
    for (unsigned int j = 0; j < m_window.getSize().y / 80 ; j++) {
        auto e = m_entityManager.addEntity("Block");
        e->setAnimation(m_assets.getAnimation("Block"));
        e->setPosition({static_cast<float>(m_window.getSize().x) - 40.0f,
                            static_cast<float>(j)*80.0f + 40.0f} );
        e->setBorderT(0);
    }

    //up
    for (unsigned int i = 1; i < m_window.getSize().x / 80 - 1 ; i++) {
        auto e = m_entityManager.addEntity("Block");
        e->setAnimation(m_assets.getAnimation("Block"));
        e->setPosition({static_cast<float>(i)*80.0f + 40.0f, 40.0f});
        e->setBorderT(0);
    }

    //down

    // auto e = m_entityManager.addEntity("Grass");
    // e->setAnimation(m_assets.getAnimation("Grass"));
    // e->setScale({ m_window.getSize().x / 80.0f, m_window.getSize().y / 80.0f});
    // e->getAnimation()->setScale(e->getScale());
    // e->setPosition({m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f});
    // e->setBorderT(0);
    // std::cout << "dimensions " << m_window.getSize().x << " " << m_window.getSize().y << "\n";
    //

    // creating the player
    m_player = m_entityManager.addPlayer("player");
    m_player->setAnimation(m_assets.getAnimation("PStand"));
    m_player->setPosition({800.0f, 800.0f});

    // todo - remove - only for cppcheck

    std::string testAnimName = "PStand";

    std::shared_ptr<Animation> animationTest;//{testAnimName, m_assets.getTexture("TexPlayer")};

    animationTest = std::make_shared<Animation>(m_assets.getAnimation(testAnimName));
    animationTest->getSprite();

    auto test = m_entityManager.addEntity("test");
    test->setAnimation(m_assets.getAnimation("MStand"));
    test->setPosition({400.0f, 400.0f});

    auto test2 = m_entityManager.addEntity("test");
    test2->setAnimation(m_assets.getAnimation("MStand"));

    if (test->collide(*test2)) {
        std::cout << "initial collision\n";
    } else {
        std::cout << "NOT collision\n";
    }
    std::cout << *m_player << "\n\n" << *test << "\n\n" << *test2 << "\n";

    // test->remove();
    // test2->remove();
    //

    m_font = m_assets.getFont("Arial");
    m_sound = m_assets.getSound("Main");
    m_sound.setLoop(true);
    m_sound.play();
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

    for (const std::shared_ptr<Entity> &e: m_entityManager.getEntities()) {
        e->draw(m_window);
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

// void Game::sLvlBuilder(std::string path) {
//     std::ifstream in (path);
//     std::string line;
// }

Game::Game(const std::string &path) {
    init(path);
}

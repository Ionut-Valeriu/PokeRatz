//
// Created by ionut on 28.01.2025.
//

#include <SFML/Graphics.hpp>

#include "Scenes/PlayScene.h"
#include "Enums.h"
#include "Monster.h"

PlayScene::PlayScene(const std::string &levelPath, sf::RenderWindow &window)
    : Scene(levelPath, window){
    init();
}

void PlayScene::init() {
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
}

void PlayScene::sRender() {
    m_window.clear(sf::Color::Black);
    m_view.setCenter(m_player->getX(), m_player->getY());
    m_window.setView(m_view);

    for (size_t i = 1; i <= EntityManager::getMaxDrawLevel(); i++) {
        for (const std::shared_ptr<Entity> &e: m_entities.getEntitiesOnLevel(i)) {
            e->draw(m_window, m_drawSprites, m_drawOutline, m_drawOrigin);
        }
    }

    m_window.display();
}

void PlayScene::update() {
    m_entities.update();
    sMovement();
    sCollision();
    sAnimation();
    sRender();

    if (!m_paused) {
        m_currentFrame++;
        m_player->incFrame();
    }
}

SceneManager PlayScene::getNext() {
    SceneManager aux = m_next;
    m_next = SceneManager::NONE;
    return aux;
}

bool PlayScene::sDoActions(ActionType type, sf::Keyboard::Key key) {
    Actions action{type, m_actions.at(key)};
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
            return true;
        }
        // default: throw;
    }
    return false;
}

void PlayScene::sAnimation() const {
    std::string animationName;

    switch (m_player->state()) {
        case AnimationState::UP:
            animationName = "PUp";
            break;

        case AnimationState::DOWN:
        case AnimationState::STAND:
            animationName = "PStand";
            break;

        case AnimationState::LEFT:
            animationName = "PSide";
            m_player->setLeft();
            break;

        case AnimationState::RIGHT:
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

void PlayScene::sCollision() {
    auto vec = m_entities.getEntities();
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
                    m_next = SceneManager::FIRST;
                }
            }
        }
    }
}

void PlayScene::sMovement() {
    for (const auto &e: m_entities.getEntities()) {
        e->updatePos();
    }
}

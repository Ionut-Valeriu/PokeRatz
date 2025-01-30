//
// Created by ionut on 28.01.2025.
//

#include "Scenes/MenuScene.h"

MenuScene::MenuScene(const std::string &file, sf::RenderWindow &window)
    : Scene(file, window) {
    init();
}

SceneManager MenuScene::getNext() {
    SceneManager aux = m_next;
    m_next = SceneManager::NONE;
    return aux;
}

void MenuScene::init() {
    registerAction(sf::Keyboard::Escape, ActionName::CLOSE);
    registerAction(sf::Keyboard::Enter, ActionName::SUBMIT);

    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
}

void MenuScene::sRender() {
    m_window.clear(sf::Color::Black);

    m_window.draw(text);

    m_window.display();
}

bool MenuScene::sDoActions(ActionType type, sf::Keyboard::Key key) {
    if (type == ActionType::START) return false;

    Actions action{type, m_actions.at(key)};
    if (action.name() == ActionName::CLOSE) { return true; }

    if (action.name() == ActionName::SUBMIT) { m_next = SceneManager::NEXT; }

    return false;
}


void MenuScene::update() {
    m_entities.update();

    sRender();

    if (!m_paused) {
        m_currentFrame++;
        // m_player->incFrame();
    }
}

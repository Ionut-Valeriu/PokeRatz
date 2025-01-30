//
// Created by ionut on 28.01.2025.
//

#include "Scene.h"

#include <utility>

void Scene::registerAction(sf::Keyboard::Key inputKey, const ActionName &aName, const Direction dir) {
    m_actions.insert({inputKey, {aName, dir}});
}

Scene::Scene(const std::string &file, sf::RenderWindow &window)
    : m_window(window) {
    m_player = m_entities.load(file, window);
}

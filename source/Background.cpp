//
// Created by ionut on 15.12.2024.
//

#include "../headers/Background.h"

Background::Background(size_t id, const std::string &tag, size_t drawLevel)
    : Entity(id, tag, drawLevel) { init(); }

void Background::onCollide(bool solid) {
    if (solid) { std::cout << "solid" << std::endl; }
    std::cout << "obj at " << m_transform->getPosition().x << "," << m_transform->getPosition().y << std::endl;
    // std::cout << "you hit something " << (solid ? "solid" : "soft") << "\n";
}

void Background::showTip(std::ostream &os) const {
    os << "Background\n";
}

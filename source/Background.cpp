//
// Created by ionut on 15.12.2024.
//

#include "../headers/Background.h"

Background::Background(size_t id, const std::string &tag, size_t drawLevel)
    : Entity(id, tag, drawLevel) { init(); }

void Background::onCollide(bool solid) {
    std::cout << "you hit something " << (solid ? "solid" : "soft") << "\n";
}

void Background::showTip(std::ostream &os) const {
    os << "Background\n";
}

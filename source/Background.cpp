//
// Created by ionut on 15.12.2024.
//

#include "../headers/Background.h"

Background::Background(size_t id, size_t drawLevel)
    : Entity(id, drawLevel) { init(); }

void Background::onCollide(bool solid) {
}

void Background::showTip(std::ostream &os) const {
    os << "Background\n";
}

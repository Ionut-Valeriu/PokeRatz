//
// Created by ionut on 15.12.2024.
//

#include "Background.h"

Background::Background(size_t id, size_t drawLevel)
    : Entity(id, drawLevel) { init(); }

void Background::onCollide(bool solid) {
    if (solid) {
        std::cout << "2 or more solids are overlapping.\n";
    }
}

void Background::showType(std::ostream &os) const {
    os << "Background\n";
}

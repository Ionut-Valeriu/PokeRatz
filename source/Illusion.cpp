//
// Created by ionut on 13.01.2025.
//

#include "../headers/Illusion.h"

Illusion::Illusion(size_t id, size_t drawLevel)
    : Entity(id, drawLevel) {}

void Illusion::onCollide(bool solid) {
    remove();
}

void Illusion::showType(std::ostream &os) const {
    os << "Illusion\n";
}

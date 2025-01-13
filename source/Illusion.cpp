//
// Created by ionut on 13.01.2025.
//

#include "../headers/Illusion.h"

Illusion::Illusion(size_t id, size_t drawLevel)
    : Entity(id, drawLevel) {
}

void Illusion::onCollide(bool solid) {
    if (solid) { m_transform->goToLastPos(); } else remove();
}

void Illusion::showType(std::ostream &os) const {
    os << "Illusion\n";
}

//
// Created by ionut on 15.12.2024.
//

#include "Entity.h"
#include "Monster.h"

Monster::Monster(size_t id, size_t drawLevel)
    : Entity(id, drawLevel) { init(); }

void Monster::onCollide(bool solid) {
    if (solid) { m_transform->goToLastPos(); } else {
        std::cout << "You killed a rat :(\n" << std::endl;
        remove();
    }
}

void Monster::showType(std::ostream &os) const {
    os << "Monster\n";
}

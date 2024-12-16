//
// Created by ionut on 15.12.2024.
//

#include "../headers/Entity.h"
#include "../headers/Monster.h"

Monster::Monster(size_t id, const std::string &tag, size_t drawLevel, size_t points)
: Entity(id, tag, drawLevel), points(points) {init();}

void Monster::init() {
    std::cout << "Monster::init()" << std::endl;
    tempShape->setOutlineThickness(0);
    m_solid = true;
    m_removable = true;
}

void Monster::onCollide() {
    remove();
}

void Monster::showTip(std::ostream &os) const {
    os << "Monster\n";
}

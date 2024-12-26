//
// Created by ionut on 15.12.2024.
//

#ifndef MONSTER_H
#define MONSTER_H

////////// INCLUDE SECTION //////////
#include "Entity.h"

////////// DESCRIPTION //////////

/// child of entity, used for elements of the monsters/enemies

////////// DEFINITION OF CLASS //////////
class Monster final : public Entity {
    // size 8
    // size_t points = 0;

public:
    Monster(size_t id, size_t drawLevel);

    void onCollide(bool solid) override;

private:
    void showType(std::ostream &os) const override;
};


#endif //MONSTER_H

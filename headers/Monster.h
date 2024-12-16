//
// Created by ionut on 15.12.2024.
//

#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"


class Monster : public Entity {
    // size 8
    // size_t points = 0;

public:
    Monster(size_t id, const std::string &tag, size_t drawLevel);

    void onCollide(bool solid) override;

private:
    void showTip(std::ostream &os) const override;
};


#endif //MONSTER_H

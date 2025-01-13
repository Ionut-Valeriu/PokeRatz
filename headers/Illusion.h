//
// Created by ionut on 13.01.2025.
//

#ifndef ILLUSION_H
#define ILLUSION_H

#include "Entity.h"


class Illusion : public Entity {
public:
    Illusion(size_t id, size_t drawLevel);

    void onCollide(bool solid) override;

private:
    void showType(std::ostream &os) const override;
};



#endif //ILLUSION_H

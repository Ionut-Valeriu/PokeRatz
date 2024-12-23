//
// Created by ionut on 15.12.2024.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity {
public:
    explicit Background(size_t id, size_t drawLevel = 1);

    void onCollide(bool solid) override;

private:
    void showTip(std::ostream &os) const override;
};


#endif //BACKGROUND_H

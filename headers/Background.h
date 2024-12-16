//
// Created by ionut on 15.12.2024.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity {
public:
    Background(size_t id, const std::string &tag, size_t drawLevel);

    void onCollide(bool solid) override;

private:
    void showTip(std::ostream &os) const override;
};


#endif //BACKGROUND_H

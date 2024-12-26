//
// Created by ionut on 15.12.2024.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

////////// INCLUDE SECTION //////////
#include "Entity.h"
////////// DESCRIPTION //////////

/// child of entity, used for elements of the background

////////// DEFINITION OF CLASS //////////
class Background final : public Entity {
public:
    explicit Background(size_t id, size_t drawLevel = 1);

    void onCollide(bool solid) override;

private:
    void showType(std::ostream &os) const override;
};


#endif //BACKGROUND_H

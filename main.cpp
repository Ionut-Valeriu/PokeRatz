#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
    Game g("resources/config/config.txt");
    g.run();

    return 0;
}

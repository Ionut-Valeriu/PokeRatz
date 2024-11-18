#include <SFML/Graphics.hpp>

#include "source/Game.h"

int main() {

    Game g("resources/config/config.txt");
    g.run();

    return 0;
}

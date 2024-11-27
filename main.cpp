#include <SFML/Graphics.hpp>

#include "headers/Game.h"

int main() {

    Game g("resources/config/config.txt");
    g.run();

    return 0;
}

#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
// #include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////

#include "source/Game.h"
#include <SFML/Audio.hpp>

int main() {
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    // init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////

    // todo - move this as an asset
    sf::SoundBuffer buffer;
    buffer.loadFromFile("resources/sounds/BumBumBum");
    sf::Sound sound(buffer);
    sound.play();
    ///

    Game g("resources/config/config.txt");
    g.run();

    return 0;
}

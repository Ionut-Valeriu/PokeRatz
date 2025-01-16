//
// Created by ionut on 06.11.2024.
//

#ifndef ASSETS_H
#define ASSETS_H

////////// INCLUDE SECTION //////////
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Animation.h"
////////// DESCRIPTION //////////

/// this class handles all assets and all assets loading

////////// DEFINITION OF CLASS //////////
class Assets {
    // size 48
    static std::map<std::string, sf::Texture> m_textureMap;
    static std::map<std::string, Animation> m_animationMap;
    static std::map<std::string, sf::Font> m_fontMap;
    static std::map<std::string, sf::SoundBuffer> m_soundBufferMap;
    static std::map<std::string, sf::Sound> m_soundMap;

    static void addTexture(const std::string &textureName, const std::string &path, bool repeated);

    static void addAnimation(const std::string &animationName, const std::string &textureName, size_t frameCount,
                             size_t speed);

    static void addFont(const std::string &fontName, const std::string &fontPath);

    static void addSoundBuffer(const std::string &bufferName, const std::string &bufferPath);

    static void addSound(const std::string &soundName, const std::string &bufferName);

public:
    Assets() = default;

    static void loadFromFile(const std::string &path);

    static const sf::Texture &getTexture(const std::string &textureName);

    static Animation &getAnimation(const std::string &animationName);

    static const sf::Font &getFont(const std::string &fontName);

    static const sf::Sound &getSound(const std::string &soundName);

    friend std::ostream &operator<<(std::ostream &os, const Assets &obj);
};


#endif //ASSETS_H

//
// Created by ionut on 06.11.2024.
//

#ifndef ASSETS_H
#define ASSETS_H
#include <map>
#include <string>
#include <memory>

#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Assets {
    // size 48
    std::map<std::string, sf::Texture> m_textureMap;
    std::map<std::string, Animation> m_animationMap;
    std::map<std::string, sf::Font> m_fontMap;
    std::map<std::string, sf::SoundBuffer> m_soundBufferMap;
    std::map<std::string, sf::Sound> m_soundMap;

    void addTexture(const std::string &textureName, const std::string &path);
    void addAnimation(const std::string &animationName, const std::string &textureName, size_t frameCount, size_t speed);
    void addFont (const std::string& fontName, const std::string& fontPath);
    void addSoundBuffer (const std::string& bufferName, const std::string& bufferPath);
    void addSound (const std::string& soundName, const std::string& bufferName);

public:
    Assets() = default;

    void loadFromFile(const std::string& path);

    [[nodiscard]] const sf::Texture& getTexture(const std::string &textureName);
    [[nodiscard]] std::shared_ptr<Animation> getAnimation(const std::string &animationName) const;
    [[nodiscard]] const sf::Font& getFont(const std::string& fontName) const;
    [[nodiscard]] const sf::Sound& getSound(const std::string& soundName) const;

    friend std::ostream & operator<<(std::ostream &os, const Assets &obj);
};



#endif //ASSETS_H

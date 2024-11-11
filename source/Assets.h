//
// Created by ionut on 06.11.2024.
//

#ifndef ASSETS_H
#define ASSETS_H
#include <map>
#include <ostream>
#include <string>

#include "Animation.h"
#include <SFML/Graphics.hpp>


class Assets {
    // size 48
    std::map<std::string, sf::Texture> m_textureMap;
    std::map<std::string, Animation> m_animationMap;
    std::map<std::string, sf::Font> m_fontMap;

    void addTexture(const std::string &textureName, const std::string &path);
    void addAnimation(const std::string &animationName, const std::string &textureName, size_t frameCount, size_t speed);
    void addFont (const std::string& fontName, const std::string& path);

public:
    Assets() = default;

    void loadFromFile(const std::string& path);

    const sf::Texture& getTexture(const std::string &textureName);
    const Animation& getAnimation(const std::string& animationName) const;
    const sf::Font& getFont(const std::string& fontName) const;

    const std::map<std::string, sf::Texture>& getTextureMap() const;
    const std::map<std::string, Animation>& getAnimationMap() const;

    friend std::ostream & operator<<(std::ostream &os, const Assets &obj);
};



#endif //ASSETS_H

//
// Created by ionut on 06.11.2024.
//

#include <fstream>
#include <memory>
#include <iostream>

#include "Assets.h"

void Assets::addTexture(const std::string &textureName, const std::string &path) {
    m_textureMap[textureName] = sf::Texture();

    if (m_textureMap[textureName].loadFromFile(path)) {
        m_textureMap[textureName].setSmooth(false);
        std::cout << "Loaded texture: " << path << std::endl;
    } else {
        std::cerr << "Failed to load texture: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
}

void Assets::addAnimation(const std::string &animationName, const std::string &textureName, size_t frameCount, size_t speed) {
    m_animationMap[animationName] = Animation(animationName, getTexture(textureName), frameCount, speed);
}

void Assets::addFont(const std::string &fontName, const std::string &path) {
    m_fontMap[fontName] = sf::Font();
    if(m_fontMap[fontName].loadFromFile(path)) {
        std::cout << "Loaded font: " << path << std::endl;
    } else {
        std::cerr << "Failed to load font: " << path << std::endl;
        m_fontMap.erase(fontName);
    }
}

void Assets::loadFromFile(const std::string &path) {
    std::ifstream file(path);
    std::string str;
    while(file.good())
    {
        file >> str;
        if (str == "Texture") {
            std::string name, texturePath;
            file >> name >> texturePath;
            addTexture(name, texturePath);
        }
        else if (str == "Animation") {
            std::string name, texture;
            size_t frames, speed;
            file >> name >> texture >> frames >> speed;
            addAnimation(name, texture, frames, speed);
        }
        else if (str == "Font") {
            std::string name, fontPath;
            file >> name >> fontPath;
            addFont(name, fontPath);
        }
        else {
            std::cerr << "Unknown Asset Type: " << str << std::endl;
        }
    }
    file.close();
}

const sf::Texture & Assets::getTexture(const std::string &textureName) {
    if (!m_textureMap.contains(textureName)) {
        std::cerr << "Texture does not exist: " << textureName << std::endl;
    }
    return m_textureMap[textureName];
}

const Animation & Assets::getAnimation(const std::string &animationName) const {
    if (!m_animationMap.contains(animationName)) {
        std::cerr << "Animation does not exist: " << animationName << std::endl;
    }
    return m_animationMap.at(animationName);
}

const sf::Font & Assets::getFont(const std::string &fontName) const {
    if (!m_fontMap.contains(fontName)) {
        std::cerr << "Font does not exist: " << fontName << std::endl;
    }
    return m_fontMap.at(fontName);
}

const std::map<std::string, sf::Texture> & Assets::getTextureMap() const {
    return m_textureMap;
}

const std::map<std::string, Animation> & Assets::getAnimationMap() const {
    return m_animationMap;
}

std::ostream & operator<<(std::ostream &os, const Assets &obj) {
    os << "Assets:\n--Textures:\n";
    for (const auto &pair : obj.m_textureMap) {
        os << "----" << pair.first << std::endl;
    }

    os << "--Animations:\n";
    for (const auto &pair : obj.m_animationMap) {
        os << "----" << pair.first << pair.second << std::endl;
    }

    os << "--Fonts:\n";
    for (const auto &pair : obj.m_fontMap) {
        os << "----" << pair.first << std::endl;
    }

    return os;
}

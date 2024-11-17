//
// Created by ionut on 06.11.2024.
//

#include <fstream>
#include <memory>
#include <iostream>
#include <SFML/Audio.hpp>

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

// void Assets::addSoundBuffer(const std::string &bufferName, const std::string &bufferPath) {
    // m_soundBufferMap[bufferName] = sf::SoundBuffer();
    //
    // if (m_soundBufferMap[bufferName].loadFromFile(bufferPath)) {
    //     std::cout << "Loaded sound buffer: " << bufferPath << std::endl;
    // } else {
    //     std::cerr << "Failed to load sound buffer: " << bufferPath << std::endl;
    //     m_soundBufferMap.erase(bufferName);
    // }
// }

// void Assets::addSound(const std::string &soundName, const std::string &bufferName) {
    // m_soundMap[soundName] = sf::Sound();
    // m_soundMap[soundName].setBuffer(m_soundBufferMap[bufferName]);
// }

void Assets::loadFromFile(const std::string &path) {
    std::ifstream file(path);
    std::string str;
    // todo - enum instead of string
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
        // else if (str == "SoundBuffer") {
        //     std::string name, bufferPath;
        //     file >> name >> bufferPath;
        //     addSoundBuffer(name, bufferPath);
        // }
        // else if (str == "Sound") {
        //     std::string name, buffername;
        //     file >> name >> buffername;
        //     addSound(name, buffername);
        // }
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

std::shared_ptr<Animation> Assets::getAnimation(const std::string &animationName) const {
    if (!m_animationMap.contains(animationName)) {
        std::cerr << "Animation does not exist: " << animationName << std::endl;
    }
    return std::make_shared<Animation>(m_animationMap.at(animationName));
}

const sf::Font & Assets::getFont(const std::string &fontName) const {
    if (!m_fontMap.contains(fontName)) {
        std::cerr << "Font does not exist: " << fontName << std::endl;
    }
    return m_fontMap.at(fontName);
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

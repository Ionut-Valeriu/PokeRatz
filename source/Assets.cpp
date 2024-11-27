//
// Created by ionut on 06.11.2024.
//

#include <fstream>
#include <memory>
#include <iostream>
#include <SFML/Audio.hpp>

#include "../headers/Assets.h"

void Assets::addTexture(const std::string &textureName, const std::string &path) {
    if(auto texture = sf::Texture(); texture.loadFromFile(path)) {
        m_textureMap.emplace( textureName, std::move(texture) );
        m_textureMap[textureName].setSmooth(false);
        std::cout << "Loaded texture: " << path << std::endl;
    } else {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
}

void Assets::addAnimation(const std::string &animationName, const std::string &textureName, size_t frameCount, size_t speed) {
    m_animationMap[animationName] = Animation(animationName, getTexture(textureName), frameCount, speed);
}

void Assets::addFont(const std::string &fontName, const std::string &path) {
    if(auto font = sf::Font(); font.loadFromFile(path)) {
        m_fontMap.emplace( fontName, std::move(font) );
        std::cout << "Loaded font: " << path << std::endl;
    } else {
        std::cerr << "Failed to load font: " << path << std::endl;
    }
}

void Assets::addSoundBuffer(const std::string &bufferName, const std::string &bufferPath) {
    if (auto soundBuffer = sf::SoundBuffer(); soundBuffer.loadFromFile(bufferPath)) {
        m_soundBufferMap.emplace( bufferName, std::move(soundBuffer) );
        std::cout << "Loaded sound buffer: " << bufferPath << std::endl;
    } else {
        std::cerr << "Failed to load sound buffer: " << bufferPath << std::endl;
    }
}

void Assets::addSound(const std::string &soundName, const std::string &bufferName) {
    m_soundMap[soundName] = sf::Sound();
    m_soundMap[soundName].setBuffer(m_soundBufferMap[bufferName]);
}

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
        else if (str == "SoundBuffer") {
            std::string name, bufferPath;
            file >> name >> bufferPath;
            addSoundBuffer(name, bufferPath);
        }
        else if (str == "Sound") {
            std::string name, buffername;
            file >> name >> buffername;
            addSound(name, buffername);
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

Animation& Assets::getAnimation(const std::string &animationName) {
    if (!m_animationMap.contains(animationName)) {
        std::cerr << "Animation does not exist: " << animationName << std::endl;
    }
    return m_animationMap.at(animationName);
}

const sf::Font & Assets::getFont(const std::string &fontName) {
    if (!m_fontMap.contains(fontName)) {
        std::cerr << "Font does not exist: " << fontName << std::endl;
    }
    return m_fontMap[fontName];
}

const sf::Sound & Assets::getSound(const std::string &soundName) const {
    return m_soundMap.at(soundName);
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

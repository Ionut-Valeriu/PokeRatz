//
// Created by ionut on 22.10.2024.
//

#include "../headers/Game.h"

#include <fstream>
#include <future>
#include <iostream>
#include <string>

#include "Actions.h"
#include "Enums.h"
#include "Assets.h"
#include "Background.h"
#include "Entity.h"
#include "Monster.h"
#include "Player.h"
#include "Exceptions.h"

void Game::addScene(const std::string &name, char type = '-', const std::string &file = "") {
    if (m_scenes.contains(name)) throw typing_error("Scene already exists" + name + "\n");

    m_currentScene = Factory<Scene>::makeScene(name, type, file, m_window);
    m_scenes[name] = m_currentScene;
    if (!m_sceneSettings.contains(name)) {
        m_sceneSettings[name] = {type, file};
    }
}

void Game::changeScene(SceneManager name) {
    std::map<std::string, std::shared_ptr<Scene> >::iterator a;
    switch (name) {
        case SceneManager::FIRST: {
            a = m_scenes.begin();

            break;
        }
        case SceneManager::NEXT: {
            a = m_scenes.find(m_sceneName);
            if (a == m_scenes.end()) {
                a = m_scenes.begin();
            } else {
                a = std::next(a);
                if (a == m_scenes.end()) {
                    a = m_scenes.begin();
                }
            }
            break;
        }
        case SceneManager::PREVIOUS:
            break;
        case SceneManager::LAST:
            break;
        case SceneManager::NONE: return;
    }

    if (m_scenes.contains(m_sceneName)) {
        m_scenes[m_sceneName].reset();
        m_scenes.erase(m_sceneName);
        addScene(m_sceneName, m_sceneSettings.at(m_sceneName).first, m_sceneSettings.at(m_sceneName).second);
    }

    m_sceneName = a->first;
    m_currentScene = a->second;
}

void Game::update() {
    changeScene(m_currentScene->getNext());
}

void Game::init(const std::string &path) {
    // loading assets and settings
    std::ifstream in{path};

    try {
        std::string keyword;
        while (in >> keyword) {
            if (keyword[0] == '-') {
                std::getline(in, keyword);
                continue;
            }
            if (keyword == "Window") {
                int width, height, framerate, r_read, g_read, b_read;
                unsigned char r, g, b;
                bool fullscreen;

                in >> width >> height >> framerate >> fullscreen >> r_read >> g_read >> b_read;
                r = r_read;
                b = b_read;
                g = g_read;

                m_window.create(sf::VideoMode(width, height), "PokeRatz",
                                fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
                m_window.setFramerateLimit(framerate);

                m_bgColor = sf::Color{r, g, b};
            } else if (keyword == "Assets") {
                std::string assetsPath;
                in >> assetsPath;
                Assets::loadFromFile(assetsPath);
            } else if (keyword == "Scene") {
                std::string name, levelPath;
                char type;
                in >> type >> name >> levelPath;
                addScene(name, type, levelPath);
                std::cout << "Scene loaded!\n";
            } else if (keyword == "View") {
                float width, height;
                in >> width >> height;
                m_view.reset({0.0f, 0.0f, width, height});
            } else if (keyword == "Sound") {
                std::string musicName;
                bool looping;
                in >> musicName >> looping;
                std::cout << musicName << "\n";
                m_sound = Assets::getSound(musicName);
                m_sound.setLoop(looping);
            } else {
                throw typing_error(keyword);
            }
        }
    } catch (const file_error &e) {
        std::cerr << "File error:\n\t" << e.what();
        // throw game_error(e.what());
    } catch (const typing_error &e) {
        std::cerr << "Typing error:\n\t" << e.what();
        // throw game_error(e.what());
    } catch (const loading_error &e) {
        std::cerr << "Loading error:\n\t" << e.what();
        // throw game_error(e.what());
    } catch (const game_error &e) {
        std::cerr << "Exit because of:\n\t" << e.what();
        exit(1);
    }

    in.close();
    std::cout << "\nInit finished!\n" << Assets() << "\n";

    changeScene(SceneManager::FIRST);
    m_sound.play();
}

void Game::run() {
    while (m_running) {
        sUserInput();
        m_currentScene->update();
        update();
    }
}

void Game::sUserInput() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            onEnd();
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            // if the current scene does not have an action associated with this key, skip the event
            // if (!getActionMap().contains(event.key.code)) { continue; }

            // determine start or end action by whether it was key pres or release
            auto type = event.type == sf::Event::KeyPressed ? ActionType::START : ActionType::END;

            // look up the action and send the action to the scene
            if (m_currentScene->sDoActions(type, event.key.code)) {
                std::cout << "on end\n";
                onEnd();
            }
        }
    }
}

void Game::onEnd() { m_running = false; }

Game::Game(const std::string &path) { init(path); }

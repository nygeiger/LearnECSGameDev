#include "headers/GameEngine.h"
#include "headers/Assets.h"
#include "headers/Scene_Play.h"
#include "headers/Scene_Menu.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

GameEngine::GameEngine(const std::string &path)
{
    init(path);
}

void GameEngine::init(const std::string &path)
{
    m_assets.loadFromFile(path);
    m_window.create(sf::VideoMode({1284, 768}), "Definitely not Mario");
    m_window.setFramerateLimit(60);

    // // ImGui::SFML::(m_window);

    // // scale the imgui ui and text size by 2
    // ImGui::GetStyle().ScaleAllSizes(2.0f);
    // ImGui::GetIO().FontGlobalScale = 2.0f;
    sf::Font tempFont;
    changeScene("MENU", std::make_shared<Scene_Menu>(tempFont, this));
}

void GameEngine::update()
{
    currentScene()->update();
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
    return m_running && m_window.isOpen();
}

const Assets &GameEngine::getAssets()
{
    return m_assets;
}

sf::RenderWindow &GameEngine::window()
{
    return m_window;
}

const bool GameEngine::debug()
{
    return m_debug;
}

void GameEngine::run()
{
    while (isRunning())
    {
        sUserInput();
        update();
    }
}

void GameEngine::quit()
{
}

void GameEngine::changeScene(Scene &scene)
{
}

void GameEngine::changeScene()
{
    sf::Font tempFont;
    m_sceneMap.erase(m_currentScene);
    m_sceneMap["MENU"] = std::make_shared<Scene_Menu>(tempFont, this);
    m_currentScene = "MENU";
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    m_sceneMap[sceneName] = scene;

    if (endCurrentScene)
    {
        m_sceneMap.erase(m_currentScene);
    }

    m_currentScene = sceneName;
}

void GameEngine::sUserInput() // mayber call it registerUserInput instead? Make sure I'm using this funct right
{
    const auto &onClose = [this](const sf::Event::Closed &)
    {
        m_window.close();
    };

    const auto &keyPressedEvent = [this](sf::Event::KeyPressed e)
    {
        const std::map sceneActionMap = currentScene()->getActionMap();
        if (sceneActionMap.find(e.scancode) != sceneActionMap.end())
        {
            currentScene()->sDoAction(Action(sceneActionMap.at(e.scancode), ActionType::START));
        }

        /// Only for debuging, don't bind key to anything else
        if (e.scancode == sf::Keyboard::Scancode::L)
        {
            m_debug = !m_debug;
        }
    };

    const auto &keyReleasedEvent = [this](sf::Event::KeyReleased e)
    {
        const std::map sceneActionMap = currentScene()->getActionMap();
        if (sceneActionMap.find(e.scancode) != sceneActionMap.end())
        {
            currentScene()->sDoAction(Action(sceneActionMap.at(e.scancode), ActionType::END));
        }
    };

    m_window.handleEvents(onClose, keyPressedEvent, keyReleasedEvent);
}
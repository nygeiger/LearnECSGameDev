// #include "../headers/GameEngine.h"
// #include "../headers/Assets.h"
// #include "../headers/Scene_Play.h"
// #include "../headers/Scene_Menu.h"
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

    // m_window.create(sf::VideoMode({1280, 768}), "Definitely not Ma");
    m_window.create(sf::VideoMode({1280, 720}), "Definitely not Ma");

    m_window.setFramerateLimit(60);

    // sUserInput();

    // // ImGui::SFML::(m_window);

    // // scale the imgui ui and text size by 2
    // ImGui::GetStyle().ScaleAllSizes(2.0f);
    // ImGui::GetIO().FontGlobalScale = 2.0f;
    sf::Font tempFont;

    // changeScene("MENU", std::make_shared<Scene_Menu>(tempFont ,*this)); // Trigger constr initial err?
    changeScene("MENU", std::make_shared<Scene_Menu>(tempFont, this)); // Trigger constr initial err?
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
// sf::RenderWindow& GameEngine::window() {
//     return m_window;
// }

void GameEngine::run()
{
    while (isRunning())
    {
        sUserInput();
        update();
    }
}

// void GameEngine::run()
// {

//     while (isRunning())
//     {
//         sUserInput();

//         m_window.clear(sf::Color::Black); // # clear the window of wnything previously drawn
//         sf::RectangleShape rect({80, 100});
//         rect.setFillColor(sf::Color::Red);
//         rect.setPosition({640, 384});

//         m_window.draw(rect);
//         m_window.display();
//     }
// }

void GameEngine::quit()
{
}

void GameEngine::changeScene(Scene &scene)
{
}

void GameEngine::changeScene()
{
    m_sceneMap.erase("scene_play");

    sf::Font tempFont;

    m_currentScene = "sene_menu";
    // m_sceneMap["scene_menu"] = std::make_shared<Scene_Menu>(tempFont ,*this); // Trigger constr initial err?
    // m_sceneMap["scene_menu"] = std::make_shared<Scene_Menu>(tempFont);
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{

    m_currentScene = sceneName;
    m_sceneMap[sceneName] = scene;

    // m_sceneMap.erase(sceneName);
}

void GameEngine::sUserInput() // mayber call it registerUserInput instead? Make sure I'm using this funct right
{
    const auto &onClose = [this](const sf::Event::Closed &)
    {
        m_window.close();
    };

    const auto &keyPressedEvent = [this](sf::Event::KeyPressed e)
    {
        if (e.scancode == sf::Keyboard::Scancode::Escape)
        {
            m_window.close();
        }
        else
        {
            const std::map sceneActionMap = currentScene()->getActionMap();
            const auto actionFromMap = sceneActionMap.find(e.scancode);

            if (actionFromMap != sceneActionMap.end())
            {
                currentScene()->sDoAction(Action(actionFromMap->second, ActionType::START));
            }
        }
    };

    const auto &keyReleasedEvent = [this](sf::Event::KeyReleased e) {};

    m_window.handleEvents(onClose, keyPressedEvent, keyReleasedEvent);
}
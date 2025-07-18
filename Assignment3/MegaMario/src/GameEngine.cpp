#include "../headers/GameEngine.h"
#include "../headers/Assets.h"
#include "../headers/Scene_Play.h"
#include "../headers/Scene_Menu.h"

#include <iostream>

GameEngine::GameEngine(const std::string& path) {
    init(path);
}

void GameEngine::init(const std::string& path) {
    m_assets.loadFromFile(path);

    m_window.create(sf::VideoMode({1280, 768}), "Definitely not Ma");
    m_window.setFramerateLimit(60);

    // // ImGui::SFML::(m_window);

    // // scale the imgui ui and text size by 2
    // ImGui::GetStyle().ScaleAllSizes(2.0f);
    // ImGui::GetIO().FontGlobalScale = 2.0f;

    changeScene("MENU", std::make_shared<Scene_Menu>(*this));
}

std::shared_ptr<Scene> GameEngine::currentScene() {
    return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning() {
    return m_running && m_window.isOpen();
}

const Assets& GameEngine::getAssets() {
    return m_assets;
}

sf::RenderWindow& GameEngine::window() {
    return m_window;
}
// sf::RenderWindow& GameEngine::window() {
//     return m_window;
// }

void GameEngine::run() {
    while (isRunning()) {
        update();
    }
}

void GameEngine::quit() {

}

void GameEngine::changeScene(Scene& scene) {
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false) {

    m_currentScene = sceneName;
    m_sceneMap[sceneName] = scene;

    m_sceneMap.erase(sceneName);

}

void GameEngine::sUserInput() {
    const auto& keyPressedEvent = [](sf::Event::KeyPressed e) {
    };

    const auto& keyReleasedEvent = [](sf::Event::KeyReleased e) {
    };

    m_window.handleEvents(keyPressedEvent, keyReleasedEvent);
}
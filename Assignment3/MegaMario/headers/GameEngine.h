#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Scene.h"
#include "Assets.h"

#include <memory>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine {
    protected:
        sf::RenderWindow m_window;
        Assets m_assets;
        std::string m_currentScene;
        SceneMap m_sceneMap;
        size_t m_simulationSpeed = 1;
        bool m_running = true;
        bool m_debug = false;

        void init(const std::string &path);
        void update();

        void sUserInput();

        std::shared_ptr<Scene> currentScene();

    public:
        GameEngine(const std::string &path);
        void changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

        void run();
        void quit();

        void changeScene(Scene &scene); // TODO: Find wich one is correct
        void changeScene(); // TODO: Find wich one is correct

        const Assets &getAssets();
        sf::RenderWindow &window();
        const bool debug();
        bool isRunning();
};

#endif
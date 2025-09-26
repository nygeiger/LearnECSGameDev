#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "Scene.h"
#include "EntityManager.h"

#include <map>
#include <memory>
#include <deque>

// enum SceneMenuActions {UP, DOWN, PLAY, QUIT}; // Use this instead of string? Does this go here or utli file (probably here)


class Scene_Menu : public Scene {
    protected:
        std::string                 m_title;
        std::vector<std::string>    m_menuStrings;
        std::vector<std::string>    m_levelPaths;
        sf::Text                    m_menuText;
        size_t                      m_selectedMenuIndex = 0;
        bool                        m_drawGrid = false;

        void init();
        void update();
        void onEnd();
        // void registerAction(sf::Keyboard::Scancode inputKey, SceneMenuActions actionName);
        void sDoInput(const Action& action);
        void drawLine(const Vec2 &p1, const Vec2 &p2) const; // TODO: dlete
        void drawGrid() const;

    public:
        Scene_Menu(const sf::Font& font, GameEngine* gameEngine);
        Scene_Menu(const Scene_Menu& obj);
        void sRender();

};

namespace SceneMenuActions {
    static const std::string UP = "UP";
    static const std::string DOWN = "DOWN";
    static const std::string PLAY ="PLAY";
    static const std::string QUIT ="QUIT";
    static const std::string TOGGLE_GRID = "TOGGLE_GRID";
};

#endif
#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "Scene.h"
#include "EntityManager.h"

#include <map>
#include <memory>
#include <deque>


class Scene_Menu : public Scene {
    protected:
        std::string                 m_title;
        std::vector<std::string>    m_menuStrings;
        std::vector<std::string>    m_levelPaths;
        sf::Text                    m_menuText;
        size_t                      m_selectedMenuIndex = 0;

        void init();
        void update();
        void onEnd();
        void sDoAction(const Action& action);

    public:
        Scene_Menu(const sf::Font& font, GameEngine* gameEngine);
        Scene_Menu(const Scene_Menu& obj);
        void sRender();

};

#endif
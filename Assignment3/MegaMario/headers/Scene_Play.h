#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "Scene.h"
// #include "Vec2.h"
#include "EntityManager.h"


#include <memory>
#include <map>


// enum ScenePlayActions {PAUSE, QUIT, TOGGLE_TEXTURE, TOGGLE_COLLISION, TOGGLE_GRID, UP};

class Scene_Play : public Scene {

    struct PlayerConfig {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

    std::shared_ptr<Entity> m_player;
    std::string             m_levelPath;
    PlayerConfig            m_playerConfig;
    bool                    m_drawTextures = true;
    bool                    m_drawCollision = false;
    bool                    m_drawGrid = false;
    const Vec2              m_gridSize = {64, 64};
    sf::Text                m_gridText;

    // Scene_Play(GameEngine* gameEngine, const std::string& levelPath, const sf::Font& font);

    void init();
    void init(const std::string& levelPath);

    void loadLevel(const std::string& filename);

    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);
    // EntityManager m_entityManager;
    void onEnd();
    void drawLine(const Vec2& p1, const Vec2& p2) const;
    // void Scene_Play::registerAction(sf::Keyboard::Scancode inputKey, ScenePlayActions actionName);
    std::shared_ptr<Entity> player();


    //Systems
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    // void sDoAction(std::string action);
    void sDoAction(const Action& action);
    void sDebug();
    void sLifespan();
    
    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);


    public:
        Scene_Play(GameEngine* gameEngine, const std::string& levelPath, const sf::Font& font);
        // Systems
        void update();
};

#endif
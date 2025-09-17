#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "Scene.h"
#include "EntityManager.h"


#include <memory>
#include <map>


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
    const Vec2              m_gridSize = {64, 64}; // TODO: All scenes should have this?
    sf::Text                m_gridText;

    void init();
    void init(const std::string& levelPath);
    void loadLevel(const std::string& filename);
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);
    void onEnd();
    void drawLine(const Vec2& p1, const Vec2& p2) const;
    void drawGrid() const;
    std::shared_ptr<Entity> player();

    //Systems
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(const Action& action);
    void sDebug();
    void sLifespan();
    
    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);


    public:
        Scene_Play(GameEngine* gameEngine, const std::string& levelPath, const sf::Font& font);
        void update();
};

/// TODO: Examine namespaces and idenfiy which can be enumerated
namespace ScenePlayActions {

    // Genearal Actions
    static const std::string PAUSE = "PAUSE";
    static const std::string TO_MAIN_MENU = "TO_MAIN_MENU";
    static const std::string TOGGLE_TEXTURE ="TOGGLE_TEXTURE";
    static const std::string TOGGLE_COLLISION ="TOGGLE_COLLISION";
    static const std::string TOGGLE_GRID = "TOGGLE_GRID";

    //Gameplay Actions
    static const std::string UP ="UP";
    static const std::string LEFT ="LEFT";
    static const std::string RIGHT = "RIGHT";
};

namespace PlayerStates {
    static const std::string STAND = "Stand";
    static const std::string JUMP = "Jump";
    static const std::string RUN = "Run";
};

#endif
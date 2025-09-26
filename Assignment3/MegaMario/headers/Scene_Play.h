#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "Scene.h"
#include "EntityManager.h"

#include <memory>
#include <map>

class Scene_Play : public Scene
{

    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

    // std::shared_ptr<Entity> m_player;
    std::string m_levelPath;
    PlayerConfig m_playerConfig;
    bool m_drawTextures = true;
    bool m_drawCollision = false;
    bool m_drawGrid = false;
    const Vec2 m_gridSize = {64, 64}; // TODO: All scenes should have this?
    // const Vec2 m_gridSize = ScenePlayUtil::GRID_SIZE;
    sf::Text m_gridText;

    void init();
    void init(const std::string &levelPath);
    void loadLevel(const std::string &filename);
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);
    void onEnd();
    void drawLine(const Vec2 &p1, const Vec2 &p2) const;
    void drawGrid() const;
    std::shared_ptr<Entity> player();

    // Systems
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoInput(const Action &action);
    void sActions();
    void sDebug();
    void sLifespan();
    /// TODO: State System???

    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

public:
    Scene_Play(GameEngine *gameEngine, const std::string &levelPath, const sf::Font &font);
    void update();
};

/// TODO: Examine namespaces and idenfiy which can be enumerated
namespace ScenePlayActions
{

    // Genearal Actions
    const std::string PAUSE = "PAUSE";
    const std::string TO_MAIN_MENU = "TO_MAIN_MENU";
    const std::string TOGGLE_TEXTURE = "TOGGLE_TEXTURE";
    const std::string TOGGLE_COLLISION = "TOGGLE_COLLISION";
    const std::string TOGGLE_GRID = "TOGGLE_GRID";

    // Gameplay Actions
    const std::string UP = "UP";
    const std::string LEFT = "LEFT";
    const std::string RIGHT = "RIGHT";
    const std::string SHOOT = "SHOOT";
};

namespace PlayerStates
{
    const std::string STAND = "Stand";
    const std::string JUMP = "Jump";
    const std::string RUN = "Run";
    // static const std::string SHOOT = "SHOOT";
};

namespace ScenePlayUtil
{
    static const Vec2 GRID_SIZE = {64, 64};

    /// @brief Bullet utils
    const Vec2 BULLET_SIZE = {8.0f, 8.0f};
    const Vec2 BULLET_VELOCITY = {14.0f, 0.0f};
    const size_t BULLET_LIFESPAN = 90.0f;
    const float SHOOT_FRAME_LIMIT = 6.0f;

    const Vec2 QUESTION_TILE_SIZE = GRID_SIZE/2;
    const Vec2 BRICK_TILE_SIZE = GRID_SIZE/2;
}

#endif
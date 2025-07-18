#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "EntityManager.h"

struct GameTextConfig
{
    int FS, R, G, B;
};
struct PlayerConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
    float S;
};
struct EnemyConfig
{
    int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI;
    float SMIN, SMAX;
};
struct BulletConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
    float S;
};

class Game
{
    sf::RenderWindow m_window; // the window we will draw to
    EntityManager m_entities;  // vector of entities to maintain
    sf::Font m_font;           // the font we will use to draw
    GameTextConfig m_gameTextConfig;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;

    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    int m_lastSpecialFireTime = 0;
    bool m_paused = false; // whether we update game logic
    bool m_running = true; // whether the game is running

    std::shared_ptr<Entity> m_player;

    void init(const std::string &path); // initialize the GameState with a config file path
    void setPaused(bool paused);        // pause the game

    void sMovement();     // System: Entity position / movement update
    void sUserInput();    // System: User Input
    void sLifespan();     // System: Lifespan
    void sRender();       // System: Render / Drawing
    void sEnemySpawner(); // System: Spawn Enemies
    void sCollision();    // System: Collisions

    void updateScore(bool increaseScore, std::shared_ptr<Entity> entity);
    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target);
    void spawnSpecialWeapon(std::shared_ptr<Entity> playerEntity, const Vec2 &target);

public:
    // Game(const std::string &config, sf::Font myFont);   // Constructor, takes in game config
    Game(const std::string &config); // Constructor, takes in game config

    void run();
};

#endif
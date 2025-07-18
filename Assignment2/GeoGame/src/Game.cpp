#include <iostream>
#include <fstream>

#include "../headers/Game.h"
#include "./Util.cpp"

Game::Game(const std::string &config)
{
    init(config);
    const bool bp = true;
}

void Game::init(const std::string &path)
{
    // TODO: read in config file here
    //      use the premade PlayerConfig, EnemyConfig, BuletConfig variables
    std::ifstream ass2ConfigFile(path); // GeoGame/config/configFile.txt
    std::string currLine;

    if (!ass2ConfigFile.is_open())
    {
        std::cerr << "Error opening the assignment file!";
    }

    while (std::getline(ass2ConfigFile, currLine))
    {
        const std::string firstWord = currLine.substr(0, currLine.find_first_of(' '));

        if (stringIsEqual(firstWord, "Window"))
        {
            // Wndow W H FL FS
            const std::vector<std::string> winParams = splitString(currLine, ' ');

            const unsigned int windowWidth = static_cast<unsigned int>(std::stoi(winParams[1]));
            const unsigned int windowHeight = static_cast<unsigned int>(std::stoi(winParams[2]));
            const int framerateLimit = std::stoi(winParams[3]);
            const bool fullScren = std::stoi(winParams[4]);

            const sf::State screenMode = fullScren ? sf::State::Fullscreen : sf::State::Windowed;

            m_window.create(sf::VideoMode({windowWidth, windowHeight}), "Assignment 2", screenMode);
            m_window.setFramerateLimit(framerateLimit);
        }
        else if (stringIsEqual(firstWord, "Font"))
        {
            // Font F S R G B
            const std::vector<std::string> fontParams = splitString(currLine, ' ');

            const std::string fontLocation = fontParams[1];
            const int fontSize = std::stoi(fontParams[2]);
            const std::uint8_t red = std::stoi(fontParams[3]);
            const std::uint8_t green = std::stoi(fontParams[4]);
            const std::uint8_t blue = std::stoi(fontParams[5]);

            sf::Font myFont;
            if (!myFont.openFromFile(fontLocation))
            {
                // # if we can't load the font, print an error to the error console and exit
                std::cerr << "Could not load font!" << std::endl;
                exit(-1);
            }
            m_font = myFont;
            m_gameTextConfig = {fontSize, red, green, blue};
        }
        else if (stringIsEqual(firstWord, "Player"))
        {
            // Player SR CR S FR FG FB OR OG OB OY V
            const std::vector<std::string> playerParams = splitString(currLine, ' ');

            const int shapeRadius = std::stoi(playerParams[1]);
            const int collisionRadius = std::stoi(playerParams[2]);
            const float speed = std::stof(playerParams[3]);
            const std::uint8_t fillR = std::stoi(playerParams[4]);
            const std::uint8_t fillG = std::stoi(playerParams[5]);
            const std::uint8_t fillB = std::stoi(playerParams[6]);
            const std::uint8_t outR = std::stoi(playerParams[7]);
            const std::uint8_t outG = std::stoi(playerParams[8]);
            const std::uint8_t outB = std::stoi(playerParams[9]);
            const int outThickness = std::stoi(playerParams[10]);
            const int shapeVerts = std::stoi(playerParams[11]);

            m_playerConfig = {shapeRadius,
                              collisionRadius,
                              fillR,
                              fillG,
                              fillB,
                              outR,
                              outG,
                              outB,
                              outThickness,
                              shapeVerts,
                              speed};
        }
        else if (stringIsEqual(firstWord, "Enemy"))
        {
            // Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI
            const std::vector<std::string> enemyParams = splitString(currLine, ' ');

            const int shapeRadius = std::stoi(enemyParams[1]);
            const int collisionRadius = std::stoi(enemyParams[2]);
            const float speedMin = std::stof(enemyParams[3]);
            const float speedMax = std::stof(enemyParams[4]);
            const int outR = std::stoi(enemyParams[5]);
            const int outG = std::stoi(enemyParams[6]);
            const int outB = std::stoi(enemyParams[7]);
            const int outThickness = std::stoi(enemyParams[8]);
            const int verticesMin = std::stoi(enemyParams[9]);
            const int verticesMax = std::stoi(enemyParams[10]);
            const int smallLifespan = std::stoi(enemyParams[11]);
            const int spawnInterval = std::stoi(enemyParams[12]);

            m_enemyConfig = {shapeRadius, collisionRadius, outR, outG, outB, outThickness, verticesMin, verticesMax, smallLifespan, spawnInterval, speedMin, speedMax};
        }
        else if (stringIsEqual(firstWord, "Bullet"))
        {
            // Bullet SR CR S FR FG FB OR OG OB OT V L
            const std::vector<std::string> bulletParams = splitString(currLine, ' ');

            const int shapeRadius = std::stoi(bulletParams[1]);
            const int collisionRadius = std::stoi(bulletParams[2]);
            const float speed = std::stof(bulletParams[3]);
            const int fillR = std::stoi(bulletParams[4]);
            const int fillG = std::stoi(bulletParams[5]);
            const int fillB = std::stoi(bulletParams[6]);
            const int outR = std::stoi(bulletParams[7]);
            const int outG = std::stoi(bulletParams[8]);
            const int outB = std::stoi(bulletParams[9]);
            const int outThickness = std::stoi(bulletParams[10]);
            const int shapeVert = std::stoi(bulletParams[11]);
            const int lifespan = std::stoi(bulletParams[12]);

            m_bulletConfig = {
                shapeRadius, collisionRadius, fillR, fillG, fillB, outR, outG, outB, outThickness, shapeVert, lifespan, speed};
        }
        else
        {
            std::cout << "Unknown line in config file: \n"
                      << currLine << std::endl;
        }
    }

    spawnPlayer();
}

void Game::run()
{
    // TODO: add pause fnctionality in here
    //      some systems should function while paused (rendering)
    //      some systems shouldn't (movement / input)

    while (m_running)
    {
        m_entities.update();

        if (!m_paused)
        {
            sLifespan();
            sEnemySpawner();
            sMovement();
            sCollision();
        }
        sUserInput();
        sRender();

        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }

    std::cout << "Running is now False --> m_running = " << m_running << std::endl;
}

void Game::setPaused(bool isPaused)
{
    m_paused = isPaused;
}

void Game::spawnPlayer()
{
    // TODO: Finish adding all properties of the palyer with the correct values from the config

    // We create every entity by calling the EntityManager.addEntity(tag)
    // This returns a std::shared_ptr<Entity>, so we use 'auto' to save typing

    auto entity = m_entities.addEntity(getEntityTypeTag(EntityType::PLAYER));

    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(0.0f, 0.0f), 0.0f);

    // The entity's shape will have radius 32, 8 sides, dark grey fill, and red outline of thickness 4
    sf::Color playerColor(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB);
    sf::Color playOutlColor(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB);
    entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, playerColor, playOutlColor, 4.0f);

    // Add an input component to the player so that we can use inputes
    entity->cInput = std::make_shared<CInput>();

    // Since we want this entity to be our player, set our Game's player variable to this Entity
    // This goes slightly against the EntityManager paradigm, but we ise the player so much it's worth the convienence
    // DONE THIS ASSIGNMENT ONLY
    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //      the enemy must be spawned completely within the bounds of the window

    // We create every entity by calling the EntityManager.addEntity(tag)
    // This returns a std::shared_ptr<Entity>, so we use 'auto' to save typing

    auto entity = m_entities.addEntity(getEntityTypeTag(EntityType::ENEMY));

    // Give this entity a Transform so it spawns at (200,200) with velocity (1,1) and an angle of 0
    // entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(10.0f, 4.0f), 0.0f);

    // Random = min + (rand() % (1 + max - min))
    float spawnX = m_enemyConfig.SR + (rand() % (1 + m_window.getSize().x - m_enemyConfig.SR));                     //// will have to change 32.0f to the radius of the shape
    float spawnY = m_enemyConfig.SR + (rand() % (1 + m_window.getSize().y - m_enemyConfig.SR));                     //// will have to change 32.0f to the radius of the shape
    float speedX = m_enemyConfig.SMIN + (rand() % (1 + static_cast<int>(m_enemyConfig.SMAX - m_enemyConfig.SMIN))); //// will have to change 32.0f to the radius of the shape
    float speedY = m_enemyConfig.SMIN + (rand() % (1 + static_cast<int>(m_enemyConfig.SMAX - m_enemyConfig.SMIN))); //// will have to change 32.0f to the radius of the shape
    float numVerts = m_enemyConfig.VMIN + (rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));                 //// will have to change 32.0f to the radius of the shape

    int enemyColorR = 0 + (rand() % (1 + 255 - 0));
    int enemyColorG = 0 + (rand() % (1 + 255 - 0));  
    int enemyColorB = 0 + (rand() % (1 + 255 - 0));     

    sf::Color enemyColor(enemyColorR, enemyColorG, enemyColorB);
    sf::Color enemyOutlColor(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB);

    entity->cTransform = std::make_shared<CTransform>(Vec2(spawnX, spawnY), Vec2(speedX, speedY), 0.0f);
    entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, numVerts, enemyColor, enemyOutlColor, 4.0f);

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

// spawns the small enemies when a big one (inpute entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> enemyEntity)
{
    // TODO: spawn small enemies at the location of the input enemy e
    // when we create the smaller enemy, we have to read the values of the original enemy

    int numSmallEnemeis = enemyEntity->cShape->circle.getPointCount();
    int angleDistance = 360 / numSmallEnemeis;
    // const float smallEnemySpeed = 2.5f;
    const float smallEnemySpeed = enemyEntity->cTransform->velocity.length() / 4;

    Vec2 target(enemyEntity->cTransform->pos.x + enemyEntity->cTransform->velocity.x, enemyEntity->cTransform->pos.y + enemyEntity->cTransform->velocity.y);
    const float distanceFromPoints = sqrtf(((enemyEntity->cTransform->pos.x - target.x) * (enemyEntity->cTransform->pos.x - target.x)) + ((enemyEntity->cTransform->pos.y - target.y) * (enemyEntity->cTransform->pos.y - target.y)));
    const Vec2 distanceVec(target.x - enemyEntity->cTransform->pos.x, target.y - enemyEntity->cTransform->pos.y);
    const Vec2 normalizedVec(distanceVec.x / distanceFromPoints, distanceVec.y / distanceFromPoints);
    const Vec2 scaledVec(smallEnemySpeed * normalizedVec.x, smallEnemySpeed * normalizedVec.y);

    for (int i = 0; i < numSmallEnemeis; i++)
    {
        const int currentRelAngle = i * angleDistance;

        auto smallEnemy = m_entities.addEntity(getEntityTypeTag(EntityType::SMALL_ENEMY));
        smallEnemy->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
        smallEnemy->cShape = std::make_shared<CShape>(enemyEntity->cShape->circle.getRadius() / numSmallEnemeis, enemyEntity->cShape->circle.getPointCount(),
                                                      enemyEntity->cShape->circle.getFillColor(), enemyEntity->cShape->circle.getOutlineColor(), enemyEntity->cShape->circle.getOutlineThickness());

        float newVelX = scaledVec.x * std::cos(degreesToRadians(enemyEntity->cTransform->angle + currentRelAngle)) - scaledVec.y * std::sin(degreesToRadians(enemyEntity->cTransform->angle + currentRelAngle));
        float newVelY = scaledVec.x * std::sin(degreesToRadians(enemyEntity->cTransform->angle + currentRelAngle)) + scaledVec.y * std::cos(degreesToRadians(enemyEntity->cTransform->angle + currentRelAngle));
        smallEnemy->cTransform = std::make_shared<CTransform>(enemyEntity->cTransform->pos, Vec2(newVelX, newVelY), enemyEntity->cTransform->angle);
    }
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> playerEntity, const Vec2 &target)
{
    // TODO: implement the spawning of a bullet which travels toward target
    //      - bullet speeed is given as a scalar speed
    //      - you must set the velocity by using formula in notes

    /*
    Vector Normalization
- Vector length = distance it travels
    - Distance from origin = (0,0)
    - L = sqrtf(x*x + y*y)
- Normalizing a vector maintains its angle, but changes its length to 1 (unit vector)
    - N = Vec2(V.x/L, V.y/L)
- Where is this useful? Example: Shooting
        - ** Assignment 2 **
    - Bullet shoot toward mouse
    - We are given speed scalar S
    - How to get speed vector?
    - D = (mx - px, my - py)
        - Difference vector
        - D has some length L, we want it to be S
    - Normalize D, N = (D.x / L, D.y / L), now has L=1
    - Vec2 velocity(S * N.x, S * N.y)
    */

    const int bulletSpeed = 30;
    const int bulletLifeSpan = 100;

    // const float distanceFromPoints = sqrtf(playerEntity->cTransform->pos.x * target.x + playerEntity->cTransform->pos.y * target.y);
    const float distanceFromPoints = sqrtf(((playerEntity->cTransform->pos.x - target.x) * (playerEntity->cTransform->pos.x - target.x)) + ((playerEntity->cTransform->pos.y - target.y) * (playerEntity->cTransform->pos.y - target.y)));
    const Vec2 distanceVec(target.x - playerEntity->cTransform->pos.x, target.y - playerEntity->cTransform->pos.y);
    const Vec2 normalizedVec(distanceVec.x / distanceFromPoints, distanceVec.y / distanceFromPoints);
    const Vec2 scaledVec(bulletSpeed * normalizedVec.x, bulletSpeed * normalizedVec.y);

    auto bullet = m_entities.addEntity(getEntityTypeTag(EntityType::BULLET));

    sf::Color bulletColor(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB);
    sf::Color bulletOutlColor(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB);

    bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, scaledVec, 0);
    bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, bulletColor, bulletOutlColor, m_bulletConfig.OT);
    bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> playerEntity, const Vec2 &target)
{
    if (m_currentFrame - m_lastSpecialFireTime >= SPECIAL_WEAPON_DELAY_FRAMES)
    {

        // TODO: implement your own special weapon
        const int specialWeaponSpeed = 15;
        // const int specialWeaponSpeed = m_bulletConfig.S;
        const int specialWeaponRadius = 10;
        const int specialWeaponEdgeCount = 8;
        const int specialWeaponLifeSpan = 100;

        const int firstSpecialBulletOffest = -15;

        // const float distanceFromPoints = sqrtf(playerEntity->cTransform->pos.x * target.x + playerEntity->cTransform->pos.y * target.y);
        const float distanceFromPoints = sqrtf(((playerEntity->cTransform->pos.x - target.x) * (playerEntity->cTransform->pos.x - target.x)) + ((playerEntity->cTransform->pos.y - target.y) * (playerEntity->cTransform->pos.y - target.y)));
        const Vec2 distanceVec(target.x - playerEntity->cTransform->pos.x, target.y - playerEntity->cTransform->pos.y);
        const Vec2 normalizedVec(distanceVec.x / distanceFromPoints, distanceVec.y / distanceFromPoints);
        const Vec2 scaledVec(specialWeaponSpeed * normalizedVec.x, specialWeaponSpeed * normalizedVec.y);

        const int specialWeaponBulletCount = 3;
        float initialAngle = 90.0f;
        float increment = 180.0f / specialWeaponBulletCount;
        float radius = playerEntity->cShape->circle.getRadius();

        float cx = playerEntity->cTransform->pos.x;
        float cy = playerEntity->cTransform->pos.y;
        // float radius = 100.0f;    // or whatever you want
        int N = specialWeaponBulletCount; // number of objects
        float startAngle = 25.0f;         // degrees
        float endAngle = 160.0f;          // degrees
        float angleStep = (endAngle - startAngle) / (N - 1);

        Vec2 tempPosVec(0, 0);

        for (int i = 0; i < specialWeaponBulletCount; i++)
        {
            float x = cos(degreesToRadians(initialAngle)) * radius;
            float y = sin(degreesToRadians(initialAngle)) * radius;

            // initialAngle -= increment;
            tempPosVec = {x, y};
        }

        for (int i = 0; i < specialWeaponBulletCount; i++)
        {
            auto specialWeapon = m_entities.addEntity(getEntityTypeTag(EntityType::SPECIAL_WEAPON));

            const auto bp = std::cos(degreesToRadians(firstSpecialBulletOffest + i * 5));
            const auto bp1 = std::sin(degreesToRadians(firstSpecialBulletOffest + i * 5));
            const auto bp2 = degreesToRadians(firstSpecialBulletOffest + i * 5);

            float newPosX = playerEntity->cTransform->pos.x * std::cos(degreesToRadians(firstSpecialBulletOffest + i * 5));
            float newPosY = playerEntity->cTransform->pos.y * std::sin(degreesToRadians(firstSpecialBulletOffest + i * 5));

            const Vec2 currBulletPos(m_player->cTransform->pos.x + (firstSpecialBulletOffest + (15 * i)), m_player->cTransform->pos.y + (firstSpecialBulletOffest + (15 * i)));
            // specialWeapon->cTransform = std::make_shared<CTransform>(currBulletPos, scaledVec, 0);
            // specialWeapon->cTransform = std::make_shared<CTransform>(Vec2(newPosX, newPosY), scaledVec, 0);
            specialWeapon->cShape = std::make_shared<CShape>(specialWeaponRadius, specialWeaponEdgeCount, sf::Color::White, sf::Color::Yellow, 2.4);
            specialWeapon->cLifespan = std::make_shared<CLifespan>(specialWeaponLifeSpan);

            float x = cos(degreesToRadians(initialAngle)) * radius;
            float y = sin(degreesToRadians(initialAngle)) * radius;

            float x2 = (cos(degreesToRadians(initialAngle)) * radius) + playerEntity->cTransform->pos.x;
            float y2 = sin(degreesToRadians(initialAngle)) * radius + playerEntity->cTransform->pos.y;
            tempPosVec = {x, y};
            const Vec2 tempPosVec2 = {x2, y2};
            // specialWeapon->cTransform = std::make_shared<CTransform>(tempPosVec2, scaledVec, 0);

            float angleDeg = startAngle + i * angleStep;
            float angleRad = degreesToRadians(angleDeg);
            float xCP = cx + cos(angleRad) * radius;
            float yCP = cy + sin(angleRad) * radius;

            // playerEntity->cTransform->pos.x

            specialWeapon->cTransform = std::make_shared<CTransform>(Vec2(xCP, yCP), scaledVec, 0);
            // Place your object at (x, y)

            initialAngle -= increment;
            m_lastSpecialFireTime = m_currentFrame;
        }

        // float cx = playerEntity->cTransform->pos.x;
        // float cy = playerEntity->cTransform->pos.y;
        // float radius = 100.0f;    // or whatever you want
        // int N = 5;                // number of objects
        // float startAngle = 45.0f; // degrees
        // float endAngle = 135.0f;  // degrees

        // float angleStep = (endAngle - startAngle) / (N - 1);

        for (int i = 0; i < N; ++i)
        {
            float angleDeg = startAngle + i * angleStep;
            float angleRad = degreesToRadians(angleDeg);
            float x = cx + cos(angleRad) * radius;
            float y = cy + sin(angleRad) * radius;
            // Place your object at (x, y)
        }

        const bool beepee = false;

        // auto specialWeapon = m_entities.addEntity(getEntityTypeTag(EntityType::SPECIAL_WEAPON));

        // specialWeapon->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, scaledVec, 0);
        // specialWeapon->cShape = std::make_shared<CShape>(specialWeaponRadius, specialWeaponEdgeCount, sf::Color::White, sf::Color::Yellow, 2.4);
        // specialWeapon->cLifespan = std::make_shared<CLifespan>(specialWeaponLifeSpan);
    }
}

void Game::updateScore(bool increaseScore, std::shared_ptr<Entity> enemyEntity)
{
    if (increaseScore)
    {
        m_score += enemyEntity->cShape->circle.getPointCount() * 100;
    }
    else
    {
        m_score--;
    }
}

void Game::sMovement()
{
    // TODO: implement all entity movement in this function
    //      you should read the m_player->cInput component to determine if the player is moving

    // Sample Movement speed update

    // ### Player Movement ### //
    m_player->cTransform->velocity = {0, 0};

    if (m_player->cInput->up || m_player->cInput->w)
        m_player->cTransform->velocity.y -= m_playerConfig.S;
    if (m_player->cInput->down || m_player->cInput->s)
        m_player->cTransform->velocity.y += m_playerConfig.S;
    if (m_player->cInput->left || m_player->cInput->a)
        m_player->cTransform->velocity.x -= m_playerConfig.S;
    if (m_player->cInput->right || m_player->cInput->d)
        m_player->cTransform->velocity.x += m_playerConfig.S;

    if ((m_player->cTransform->pos.x - m_player->cShape->circle.getRadius() - m_player->cShape->circle.getOutlineThickness() >= 0 || m_player->cTransform->velocity.x > 0) && (m_player->cTransform->pos.x + m_player->cShape->circle.getRadius() + m_player->cShape->circle.getOutlineThickness() <= m_window.getSize().x || m_player->cTransform->velocity.x < 0))
        m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    if ((m_player->cTransform->pos.y - m_player->cShape->circle.getRadius() - m_player->cShape->circle.getOutlineThickness() >= 0 || m_player->cTransform->velocity.y > 0) && (m_player->cTransform->pos.y + m_player->cShape->circle.getRadius() + m_player->cShape->circle.getOutlineThickness() <= m_window.getSize().y || m_player->cTransform->velocity.y < 0))
        m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
    // ### End Player Movement ### //

    // ### Eemey Movement ### //
    for (auto e : m_entities.getEntities(getEntityTypeTag(EntityType::ENEMY)))
    {
        if ((e->cTransform->pos.x - e->cShape->circle.getRadius() - e->cShape->circle.getOutlineThickness() <= 0 && e->cTransform->velocity.x < 0) || (e->cTransform->pos.x + e->cShape->circle.getRadius() + e->cShape->circle.getOutlineThickness() >= m_window.getSize().x && e->cTransform->velocity.x > 0))
            e->cTransform->velocity.x *= -1;
        if ((e->cTransform->pos.y - e->cShape->circle.getRadius() - e->cShape->circle.getOutlineThickness() <= 0 && e->cTransform->velocity.y < 0) || (e->cTransform->pos.y + e->cShape->circle.getRadius() + e->cShape->circle.getOutlineThickness() >= m_window.getSize().y && e->cTransform->velocity.y > 0))
            e->cTransform->velocity.y *= -1;

        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
    // ### End Enemy Movement ### //

    // ### Bullet Movement ### //
    for (auto e : m_entities.getEntities(getEntityTypeTag(EntityType::SMALL_ENEMY)))
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
    // ### End Bullet Movement ### //

    // ### Bullet Movement ### //
    for (auto e : m_entities.getEntities(getEntityTypeTag(EntityType::BULLET)))
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
    // ### End Bullet Movement ### //

    // ### Special Weapon Movement ### //
    for (auto e : m_entities.getEntities(getEntityTypeTag(EntityType::SPECIAL_WEAPON)))
    {
        if ((e->cTransform->pos.x - e->cShape->circle.getRadius() - e->cShape->circle.getOutlineThickness() <= 0 && e->cTransform->velocity.x < 0) || (e->cTransform->pos.x + e->cShape->circle.getRadius() + e->cShape->circle.getOutlineThickness() >= m_window.getSize().x && e->cTransform->velocity.x > 0))
            e->cTransform->velocity.x *= -1;
        if ((e->cTransform->pos.y - e->cShape->circle.getRadius() - e->cShape->circle.getOutlineThickness() <= 0 && e->cTransform->velocity.y < 0) || (e->cTransform->pos.y + e->cShape->circle.getRadius() + e->cShape->circle.getOutlineThickness() >= m_window.getSize().y && e->cTransform->velocity.y > 0))
            e->cTransform->velocity.y *= -1;

        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
    // ### End Special Weapon Movement ### //

    // m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    // m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sLifespan()
{
    // TODO implement all lifespan functionality
    //
    // for all entities
    //      if entity has no lifespan component, skip it
    //      if entity has > 0 lifespan, subtract 1
    //      if it has lifespan and is alive
    //          scale its alpha channel properly
    //      if it has lifespan and its time is up
    //          destroy the entity

    for (auto entity : m_entities.getEntities())
    {
        if (entity->cLifespan)
        {
            entity->cLifespan->remaining -= 1;
            if (entity->cLifespan->remaining <= 0)
            {
                entity->destroy();
            }
            else
            {
                const float remLifeRatio = entity->cLifespan->remaining / static_cast<float>(entity->cLifespan->total);
                const float opacityLevel = 255 * remLifeRatio;
                ;

                const sf::Color currentEntityColor = entity->cShape->circle.getFillColor();
                sf::Color colorWithOpac(currentEntityColor.r, currentEntityColor.b, currentEntityColor.g, opacityLevel);
                entity->cShape->circle.setFillColor(colorWithOpac);

                const sf::Color currentEntityOutColor = entity->cShape->circle.getOutlineColor();
                sf::Color outColorWithOpac(currentEntityOutColor.r, currentEntityOutColor.b, currentEntityOutColor.g, opacityLevel);
                entity->cShape->circle.setOutlineColor(outColorWithOpac);
            }
        }
    }
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities
    //      be sure to use the collision radius, NOT the shape radius

    for (auto bullet : m_entities.getEntities(getEntityTypeTag(EntityType::BULLET)))
    {
        for (auto enemy : m_entities.getEntities(getEntityTypeTag(EntityType::ENEMY)))
        {
            if (bullet->cTransform->pos.dist(enemy->cTransform->pos) <= m_enemyConfig.CR || bullet->cTransform->pos.dist(enemy->cTransform->pos) <= m_bulletConfig.CR)
            {
                bullet->destroy();
                spawnSmallEnemies(enemy);
                enemy->destroy();
                updateScore(true, enemy);
            }
        }
    }

    for (auto specialWeapon : m_entities.getEntities(getEntityTypeTag(EntityType::SPECIAL_WEAPON)))
    {
        for (auto enemy : m_entities.getEntities(getEntityTypeTag(EntityType::ENEMY)))
        {
            if (specialWeapon->cTransform->pos.dist(enemy->cTransform->pos) <= m_enemyConfig.CR || specialWeapon->cTransform->pos.dist(enemy->cTransform->pos) <= m_bulletConfig.CR)
            {
                spawnSmallEnemies(enemy);
                enemy->destroy();
                updateScore(true, enemy);
            }
        }
    }

    for (auto player : m_entities.getEntities(getEntityTypeTag(EntityType::PLAYER)))
    {
        for (auto enemy : m_entities.getEntities(getEntityTypeTag(EntityType::ENEMY)))
        {
            if (player->cTransform->pos.dist(enemy->cTransform->pos) <= m_enemyConfig.CR || player->cTransform->pos.dist(enemy->cTransform->pos) <= m_playerConfig.CR)
            {
                spawnSmallEnemies(enemy);
                enemy->destroy();
                updateScore(false, enemy);
            }
        }
    }
}

void Game::sEnemySpawner()
{
    // TODO: code which implements enemy spawning should go here
    //
    //      (use m_currentFrame - m_lastEnemySpawnTime) to determine
    //      how long it has been since the last enemy spawned

    // if (m_currentFrame - m_lastEnemySpawnTime >= 60 * 3)
    // {
    //     spawnEnemy();
    // }

    if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
    {
        spawnEnemy();
    }
}

void Game::sRender()
{
    // TODO: change the code below to draw ALL of the entities
    //      sample drawing of the player Entity that we have created

    std::cout << "In sRender" << std::endl;

    m_window.clear(sf::Color::Black);

    // set the position of the shape based on the entity's transform->pos
    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(sf::degrees(m_player->cTransform->angle));
    m_player->cShape->circle.setPosition({m_player->cTransform->pos.x, m_player->cTransform->pos.y});

    // draw the entity's sf::CircleShape
    // m_window.draw(m_player->cShape->circle);

    for (auto e : m_entities.getEntities())
    {
        // set the position of the shape based on the entity's transform pos
        e->cShape->circle.setPosition({e->cTransform->pos.x, e->cTransform->pos.y});

        // set the rotation of the shape based on the entity's transform angle
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(sf::degrees(e->cTransform->angle));

        // draw the entity's sf::CircleShape
        m_window.draw(e->cShape->circle);
    }

    // sf::Font myFont;
    // std::string fontLocation = "../fonts/Bytesized/Bytesized-Regular.ttf";
    // if (!myFont.openFromFile(fontLocation))
    // {
    //     // # if we can't load the font, print an error to the error console and exit
    //     std::cerr << "Could not load font!" << std::endl;
    //     exit(-1);
    // }

    sf::Color textColor(m_gameTextConfig.R, m_gameTextConfig.G, m_gameTextConfig.B);
    if (m_paused)
    {
        sf::Text pausedText(m_font, "GAME PAUSED");
        // pausedText.setCharacterSize(100);
        pausedText.setCharacterSize(m_gameTextConfig.FS);
        float mWX = m_window.getSize().x / 2;
        float mWY = m_window.getSize().y / 2;
        pausedText.setPosition({mWX, mWY});
        // pausedText.setFillColor(sf::Color::White);
        pausedText.setFillColor(textColor);
        m_window.draw(pausedText);
    }

    // sf::Text gameScore(myFont, "SCORE: " + std::to_string(m_score));
    sf::Text gameScore(m_font, "SCORE: " + std::to_string(m_score));
    gameScore.setCharacterSize(50);
    // gameScore.setCharacterSize(m_gameTextConfig.FS);
    float mWX = m_window.getSize().x / 2;
    float mWY = 20;
    gameScore.setPosition({mWX, mWY});
    // gameScore.setFillColor(sf::Color::White);
    gameScore.setFillColor(textColor);
    m_window.draw(gameScore);

    m_window.display();
}

void Game::sUserInput()
{
    // TODO: handle user input here
    //      note that you should only be setting the player's input conponent variables here
    //      you should not implement the player's movement logic here
    //      the movement system will read the variables you set in this function

    const auto onClose = [this](sf::Event::Closed)
    {
        m_running = false;
    };

    const auto onKeyPressed = [this](const sf::Event::KeyPressed event)
    {
        switch (event.scancode)
        {
        case sf::Keyboard::Scancode::Up:
            std::cout << "Up Key Pressed" << std::endl;
            m_player->cInput->up = true;
            break;
        case sf::Keyboard::Scancode::W:
            std::cout << "Up Key Pressed" << std::endl;
            m_player->cInput->w = true;
            break;

        case sf::Keyboard::Scancode::Down:
            std::cout << "Down Key Pressed" << std::endl;
            m_player->cInput->down = true;
            break;
        case sf::Keyboard::Scancode::S:
            std::cout << "Down Key Pressed" << std::endl;
            m_player->cInput->s = true;
            break;

        case sf::Keyboard::Scancode::Left:
            std::cout << "Left Key Pressed" << std::endl;
            m_player->cInput->left = true;
            break;
        case sf::Keyboard::Scancode::A:
            std::cout << "Left Key Pressed" << std::endl;
            m_player->cInput->a = true;
            break;

        case sf::Keyboard::Scancode::Right:
            std::cout << "Right Key Pressed" << std::endl;
            m_player->cInput->right = true;
            break;
        case sf::Keyboard::Scancode::D:
            std::cout << "Right Key Pressed" << std::endl;
            m_player->cInput->d = true;
            break;

        case sf::Keyboard::Scancode::P:
            std::cout << "\"P\" Key Pressed" << std::endl;
            // m_paused = ~m_paused;
            m_paused = m_paused ? false : true;
            break;

        case sf::Keyboard::Scancode::Escape:
            std::cout << "\"P\" Key Pressed" << std::endl;
            // m_paused = ~m_paused;
            m_running = false;
            break;
        default:
            break;
        }

        const bool bp = true;

        if (m_player->cInput->up == true)
        {
            const bool bp2 = true;
        }
    };

    const auto onKeyReleased = [this](const sf::Event::KeyReleased event)
    {
        switch (event.scancode)
        {
        case sf::Keyboard::Scancode::Up:
            std::cout << "Up Key Released" << std::endl;
            m_player->cInput->up = false;
            break;
        case sf::Keyboard::Scancode::W:
            std::cout << "Up Key Released" << std::endl;
            m_player->cInput->w = false;
            break;

        case sf::Keyboard::Scancode::Down:
            std::cout << "Down Key Released" << std::endl;
            m_player->cInput->down = false;
            break;
        case sf::Keyboard::Scancode::S:
            std::cout << "Down Key Released" << std::endl;
            m_player->cInput->s = false;
            break;

        case sf::Keyboard::Scancode::Left:
            std::cout << "Left Key Released" << std::endl;
            m_player->cInput->left = false;
            break;

        case sf::Keyboard::Scancode::A:
            std::cout << "Left Key Released" << std::endl;
            m_player->cInput->a = false;
            break;

        case sf::Keyboard::Scancode::Right:
            std::cout << "Right Key Released" << std::endl;
            m_player->cInput->right = false;
            break;
        case sf::Keyboard::Scancode::D:
            std::cout << "Right Key Released" << std::endl;
            m_player->cInput->d = false;
            break;

        default:
            break;
        }
        const bool bp = true;
    };

    const auto onMouseButtonPressed = [this](const sf::Event::MouseButtonPressed event)
    {
        Vec2 mousePosition(event.position.x, event.position.y);

        if (!m_paused && event.button == sf::Mouse::Button::Left)
        {
            std::cout << "Left Mouse Button Clicked at (" << event.position.x << "," << event.position.y
                      << ")" << std::endl;

            // call spawnBullet here
            spawnBullet(m_player, Vec2(event.position.x, event.position.y));
        }

        if (!m_paused && event.button == sf::Mouse::Button::Right)
        {
            std::cout << "Right Mouse Button Clicked at (" << event.position.x << "," << event.position.y
                      << ")" << std::endl;

            // call spawnSpecialWeapon here
            spawnSpecialWeapon(m_player, Vec2(event.position.x, event.position.y));
        }

        const bool bp = true;
    };

    m_window.handleEvents(onClose, onKeyPressed, onKeyReleased, onMouseButtonPressed);
}

/*
g++ -std=c++17 Game.cpp -o CLgame -I/opt/homebrew/Cellar/sfml/3.0.0_1/include -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-window -lsfml-graphics -lsfml-system
*/
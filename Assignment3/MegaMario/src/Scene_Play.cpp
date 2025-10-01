#include "headers/Scene_Play.h"
#include "headers/Physics.h"
#include "headers/Assets.h"
#include "headers/GameEngine.h"
#include "headers/Components.h"
#include "headers/Action.h"
#include "Util.cpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

Scene_Play::Scene_Play(GameEngine *gameEngine, const std::string &levelPath, const sf::Font &font)
    : Scene(gameEngine), m_gridText(sf::Text(font)), m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Scene_Play::init(const std::string &levelPath)
{
    registerAction(sf::Keyboard::Scancode::P, ScenePlayActions::PAUSE);
    registerAction(sf::Keyboard::Scancode::Escape, ScenePlayActions::TO_MAIN_MENU);
    registerAction(sf::Keyboard::Scancode::T, ScenePlayActions::TOGGLE_TEXTURE);
    registerAction(sf::Keyboard::Scancode::C, ScenePlayActions::TOGGLE_COLLISION);
    registerAction(sf::Keyboard::Scancode::G, ScenePlayActions::TOGGLE_GRID);
    registerAction(sf::Keyboard::Scancode::W, ScenePlayActions::UP);
    registerAction(sf::Keyboard::Scancode::A, ScenePlayActions::LEFT);
    registerAction(sf::Keyboard::Scancode::D, ScenePlayActions::RIGHT);
    registerAction(sf::Keyboard::Scancode::Space, ScenePlayActions::SHOOT);
    registerAction(sf::Keyboard::Scancode::F, ScenePlayActions::CONTINUE_GAME);

    m_gridText.setCharacterSize(12);

    loadLevel(levelPath);
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    //  TODO:   This function takes in a grid position (x,y) and an Entity
    //          Return a Vec2 indicating where the CENTER position of the Entity should be
    //          You must use the Entity's Animation size to position it correctly
    //          The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
    //          The bottom-left corner of the Animation should aligh with of the grid cell

    return Vec2(0, 0);
}

void Scene_Play::loadLevel(const std::string &fileName)
{
    // reset the entity manager every time we load a level
    m_entityManager = EntityManager();

    // TODO: read in the level file and add the appropriate entities
    //       use the PlayerConfig struct m_playerConfig to store player properties
    //       this struct is defined at the top of Scene_Play.h

    std::ifstream file(fileName);
    if (file.bad())
    {
        std::cerr << "FAILED to load level file: " << fileName << std::endl;
    }

    while (file.good())
    {
        std::string lineHeader;
        file >> lineHeader;

        /// TODO: Logic for positioning tiles NOT the same size of a gird block is iffy. Especially with floats
        if (lineHeader == "Tile")
        {
            auto tile = m_entityManager.addEntity(EntityType::TILE);
            std::string animationName;
            file >> animationName;

            if (animationName == AnimationType::BLOCK)
            {
                int gx, gy;
                file >> gx >> gy;

                tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(animationName), false);
                tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));

                /// Only leaving the following for quick glance at original logic
                const Vec2 textureSize = tile->getComponent<CAnimation>().animation.getSize();
                const Vec2 textToGridBlockRatio(m_gridSize.x / textureSize.x, m_gridSize.y / textureSize.y);
                tile->getComponent<CTransform>().scale = textToGridBlockRatio;
                tile->addComponent<CBoundingBox>(textureSize * textToGridBlockRatio);
            }
            else if (animationName == AnimationType::BRICK)
            {
                float gx, gy;
                file >> gx >> gy;

                tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(animationName), false);
                tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));

                const Vec2 &textureSize = tile->getComponent<CAnimation>().animation.getSize();
                const Vec2 textToGridBlockRatio = getTextureToSizeRatio(textureSize, ScenePlayUtil::BRICK_TILE_SIZE);
                tile->getComponent<CTransform>().scale = textToGridBlockRatio;
                tile->addComponent<CBoundingBox>(textureSize * textToGridBlockRatio);
            }
            else if (animationName == AnimationType::QUESTION)
            {
                float gx, gy;
                file >> gx >> gy;

                tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(animationName), true);
                tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));

                const Vec2 &textureSize = tile->getComponent<CAnimation>().animation.getSize();
                const Vec2 textToGridBlockRatio = getTextureToSizeRatio(textureSize, ScenePlayUtil::QUESTION_TILE_SIZE);
                tile->getComponent<CTransform>().scale = textToGridBlockRatio;
                tile->addComponent<CBoundingBox>(textureSize * textToGridBlockRatio);
            }
        }
        else if (lineHeader == "Flag")
        {
            auto tile = m_entityManager.addEntity(EntityType::FLAG);
            std::string animationName;
            file >> animationName;

            if (animationName == AnimationType::FLAG)
            {
                float gx, gy;
                file >> gx >> gy;

                tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(animationName), true);
                tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));
                // tile->addComponent<CTransform>(Vec2(gx, gy));

                const Vec2 &textureSize = tile->getComponent<CAnimation>().animation.getSize();
                const Vec2 textToGridBlockRatio = getTextureToSizeRatio(textureSize, ScenePlayUtil::FLAG_TILE_SIZE);
                tile->getComponent<CTransform>().scale = textToGridBlockRatio;
                tile->addComponent<CBoundingBox>(textureSize * textToGridBlockRatio);
                auto newTextSize = textureSize * textToGridBlockRatio;
                auto tempVari = (int)newTextSize.x % 64;
                auto tempVar = (int)newTextSize.y % 64;
                // tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));
            }
        }
        else if (lineHeader == "FlagPole")
        {

            auto tile = m_entityManager.addEntity(EntityType::FLAG_POLE);
            std::string animationName;
            file >> animationName;

            if (animationName == AnimationType::FLAGPOLE)
            {
                float gx, gy;
                file >> gx >> gy;

                tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(animationName), true);
                tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));

                const Vec2 &textureSize = tile->getComponent<CAnimation>().animation.getSize();
                const Vec2 textToGridBlockRatio = getTextureToSizeRatio(textureSize, ScenePlayUtil::FLAGPOLE_TILE_SIZE);
                tile->getComponent<CTransform>().scale = textToGridBlockRatio;
                tile->addComponent<CBoundingBox>(textureSize * textToGridBlockRatio);
                auto newTextSize = textureSize * textToGridBlockRatio;
            }
        }
        else
        {
            std::string tempLine;
            std::getline(file, tempLine);
        }
    }
    spawnPlayer();
}

void Scene_Play::spawnPlayer()
{
    // TODO: be sure to addd the remaining components to the palyer
    // be sure to destroy the dead player if you're respawning
    std::shared_ptr<Entity> playerEnt = player();
    playerEnt->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::STAND), true);
    playerEnt->addComponent<CTransform>(Vec2(m_game->window().getDefaultView().getCenter().x, m_game->window().getDefaultView().getCenter().y));
    playerEnt->addComponent<CBoundingBox>((playerEnt->getComponent<CAnimation>().animation.getSize() - Vec2(16, 16)));
    playerEnt->addComponent<CState>("STAND");
    playerEnt->addComponent<CInput>();
    playerEnt->addComponent<CGravity>(1);
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
    // TODO: this should spawn a bullet at (from) the given entity, going in the direction the entity is facing
    const Vec2 sourceEntityLocation = entity->getComponent<CTransform>().pos;
    const bool entitySourceFaceRight = (entity->getComponent<CTransform>().scale.x >= 0);

    Vec2 bulletSpawnPos = sourceEntityLocation;
    bulletSpawnPos.x += entitySourceFaceRight ? 5 : -5;

    auto bullet = m_entityManager.addEntity(EntityType::BULLET);
    bullet->addComponent<CTransform>(bulletSpawnPos);
    bullet->getComponent<CTransform>().velocity = entitySourceFaceRight ? ScenePlayUtil::BULLET_VELOCITY : ScenePlayUtil::BULLET_VELOCITY * -1;
    bullet->addComponent<CLifespan>(ScenePlayUtil::BULLET_LIFESPAN, m_currentFrame);
    bullet->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::BULLET), false);

    Vec2 bulletAniToSizeRation = getTextureToSizeRatio(bullet->getComponent<CAnimation>().animation.getSize(), ScenePlayUtil::BULLET_SIZE);
    bullet->getComponent<CTransform>().scale = bulletAniToSizeRation;
    bullet->addComponent<CBoundingBox>(bullet->getComponent<CAnimation>().animation.getSize() * bulletAniToSizeRation);
}

void Scene_Play::update()
{
    m_entityManager.update();

    if (!m_paused && !m_gameOver)
    {
        sMovement();
        sActions();
        sLifespan();
        sCollision();
        // sAnimation();
    }

    sAnimation();
    sRender();

    // TODO implement pause functionality

    //     sMovement();
    //     sLifespan();
    //     sCollision();
    //     // sRender();
    //     sAnimation();
    //     // sRender();
    m_currentFrame++;
}

void Scene_Play::sMovement()
{
    // TODO: Implement player movement / jumpinng based onn its CInput component
    // TODO: Implement gravity's effect on the player
    // TODO: Implement the maximum player speed in both x and y directions
    // NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right

    const float playerLowestPoint = 12 * m_gridSize.y;
    const float xMaxSpeed = 7.0f;
    const float xMaxSpeedInv = xMaxSpeed * -1;
    const float yMaxSpeed = 25.0f;
    const float yMaxSpeedInv = yMaxSpeed * -1;
    const float runSpeed = 4.75;

    for (auto e : m_entityManager.getEntities()) // Thorugh all Ents or just those that move?
    {
        if (e->hasComponent<CTransform>())
        {
            /// ##### Entity Gravity Logic #####
            if (e->hasComponent<CGravity>())
            {
                e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
            }
            /// ##### End Entity Gravity Logic #####

            /// ##### Player Entity Specific Logic #####
            if (e->tag() == EntityType::PLAYER)
            {
                auto &playerInput = e->getComponent<CInput>();
                auto &playerPos = e->getComponent<CTransform>().pos;
                if (playerInput.left)
                {
                    e->getComponent<CTransform>().velocity.x = -runSpeed;
                }
                else if (playerInput.right)
                {
                    e->getComponent<CTransform>().velocity.x = runSpeed;
                }
                else
                {
                    e->getComponent<CTransform>().velocity.x = 0;
                }

                if (playerInput.canJump && playerInput.up)
                {
                    e->getComponent<CTransform>().velocity.y = -17;
                    auto &playerInput = e->getComponent<CInput>().canJump = false;
                    e->addComponent<CState>(PlayerStates::JUMP);
                    e->addComponent<CGravity>(1);
                }

                if (playerPos.y > playerLowestPoint)
                {
                    e->addComponent<CTransform>(Vec2(m_game->window().getDefaultView().getCenter().x, m_game->window().getDefaultView().getCenter().y));
                }

                if (playerPos.x - e->getComponent<CTransform>().velocity.x <= 0 && e->getComponent<CTransform>().velocity.x < 0)
                {
                    e->getComponent<CTransform>().velocity.x = 0;
                }

                // if entity is moving faster than max speed in any direction
                // set the speed to the max
                if (e->getComponent<CTransform>().velocity.y > yMaxSpeed)
                {
                    e->getComponent<CTransform>().velocity.y = yMaxSpeed;
                }
                if (e->getComponent<CTransform>().velocity.x > xMaxSpeed)
                {
                    e->getComponent<CTransform>().velocity.x = xMaxSpeed;
                }
                if (e->getComponent<CTransform>().velocity.y < yMaxSpeedInv)
                {
                    e->getComponent<CTransform>().velocity.y = yMaxSpeedInv;
                }
                if (e->getComponent<CTransform>().velocity.x < xMaxSpeedInv)
                {
                    e->getComponent<CTransform>().velocity.x = xMaxSpeedInv;
                }
            }
            /// ##### End Player Entity Specific Logic #####

            e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;
            e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
        }
    }
}

void Scene_Play::sLifespan()
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

    for (auto entity : m_entityManager.getEntities())
    {
        if (entity->hasComponent<CLifespan>())
        {
            auto &entityCLifespan = entity->getComponent<CLifespan>();
            const size_t reaminingLifespan = entityCLifespan.lifespan - (m_currentFrame - entityCLifespan.frameCreated);
            if (reaminingLifespan <= 0)
            {
                entity->destroy();
            }
            else if (entityCLifespan.fadeOut)
            {
                const float remLifeRatio = reaminingLifespan / static_cast<float>(entityCLifespan.lifespan);
                const float opacityLevel = 255 * remLifeRatio;

                const sf::Color currentEntityColor = entity->getComponent<CAnimation>().animation.getSprite().getColor();
                sf::Color colorWithOpac(currentEntityColor.r, currentEntityColor.b, currentEntityColor.g, opacityLevel);
                // entity->getComponent<CAnimation>().animation.getSprite().setColor(colorWithOpac);
            }
        }
    }
}

/**
 * Helper functions only used to help debug during collision development
 *currently only works with one moving and one stationary object
 */
/// @brief To create an entity with the location and size of the collision area of two entities
void createCollisionAreaEntity(EntityManager &entityManager, const bool &playerCameFromRight, const bool &playerCameFromBottom, std::shared_ptr<Entity> movingEnt, const Vec2 &overlapVec)
{
    auto collisionVisualEnt = entityManager.addEntity(EntityType::COLLISION_VISUAL);
    const float collVisXPoint = (playerCameFromRight) ? movingEnt->getComponent<CTransform>().pos.x - movingEnt->getComponent<CBoundingBox>().halfsize.x : movingEnt->getComponent<CTransform>().pos.x + movingEnt->getComponent<CBoundingBox>().halfsize.x;
    const float collVisYPoint = (playerCameFromBottom) ? movingEnt->getComponent<CTransform>().pos.y - movingEnt->getComponent<CBoundingBox>().halfsize.y : movingEnt->getComponent<CTransform>().pos.y + movingEnt->getComponent<CBoundingBox>().halfsize.y;
    collisionVisualEnt->addComponent<CTransform>(Vec2(collVisXPoint, collVisYPoint));
    collisionVisualEnt->addComponent<CBoundingBox>(overlapVec);
}

/// @brief To highlight the tile entity specified (by created an entity overlapping the tiles outline)
void createCollisionTileEntity(EntityManager &entityManager, std::shared_ptr<Entity> tileEnt)
{
    auto collisionVisualEnt = entityManager.addEntity(EntityType::COLLISION_VISUAL);
    collisionVisualEnt->addComponent<CTransform>(tileEnt->getComponent<CTransform>());
    collisionVisualEnt->addComponent<CBoundingBox>(tileEnt->getComponent<CBoundingBox>());
}
/**
 * Collision Helper Function End
 */

void Scene_Play::sCollision()
{
    // REMEMBER: SFML's (0,0) position is on the TOP-LEFT corner
    //  This means jumping will have a negative y-component
    // and gravity will have a positive y-component
    // Also, something BELOW something else will have a y value GREATER than it
    // Also, something ABOVE something will ahve a y value LESS than it

    // TODO: Implement Physics::GetOverlap() function, use it inside this function

    // TODO: Implement bullet / tile collisions
    //      Destroy the tile if it has a Brick Animation

    // TODO: Implement player / tile collisions and resolutions
    //      Update the CState component of the player to store wheter it is currently on ground or in the air.
    //      This will be used in the Animation system

    /// TODO: Logic to make sure edge cases are considered ex: high velocity (although it's limited in each direction)

    /// @brief Check for Tile x Player Collisions
    auto playerEnt = player();
    for (auto &tileEnt : m_entityManager.getEntities(EntityType::TILE))
    {
        if (tileEnt->hasComponent<CBoundingBox>())
        {
            // const Vec2 overlapVec = Physics::GetOverlap(tileEnt, m_player);
            const Vec2 overlapPlayerVec = Physics::GetOverlap(tileEnt, playerEnt);
            if (Physics::IsOverlap(overlapPlayerVec))
            {
                const Vec2 prevPlayerOverlapVec = Physics::GetPreviousOverlap(tileEnt, playerEnt);
                CTransform playerTrans = playerEnt->getComponent<CTransform>();
                CBoundingBox playerBBox = playerEnt->getComponent<CBoundingBox>();

                const bool playerCameFromRight = playerEnt->getComponent<CTransform>().prevPos.x > playerEnt->getComponent<CTransform>().pos.x;
                const bool playerCameFromBottom = playerEnt->getComponent<CTransform>().prevPos.y > playerEnt->getComponent<CTransform>().pos.y;

                if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BLOCK)
                {
                    if (prevPlayerOverlapVec.y <= 0 && prevPlayerOverlapVec.x > 0) // Entities collided via y-axis i.e. Megaman landing on a block
                    {
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapPlayerVec.y : -overlapPlayerVec.y;
                        if (playerCameFromBottom)
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                        }
                        else
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CInput>().canJump = true;
                            if (!Physics::IsOverlap(prevPlayerOverlapVec))
                                playerEnt->addComponent<CState>(playerEnt->getComponent<CInput>().left || playerEnt->getComponent<CInput>().right ? PlayerStates::RUN : PlayerStates::STAND);
                        }
                    }
                    else if (prevPlayerOverlapVec.x <= 0 && prevPlayerOverlapVec.y > 0) // Entities collided via x-axis i.e. Megaman running into pipe
                    {
                        playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapPlayerVec.x : -overlapPlayerVec.x;
                    }
                    else if (prevPlayerOverlapVec.x >= 0 && prevPlayerOverlapVec.y >= 0 && overlapPlayerVec.x >= 0 && overlapPlayerVec.y >= 0)
                    {
                        const auto bp = true;
                        // playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapPlayerVec.x : -overlapPlayerVec.x;
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapPlayerVec.y : -overlapPlayerVec.y;

                        if (m_game->debug())
                        {
                            createCollisionTileEntity(m_entityManager, tileEnt);
                        }
                    }
                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, playerEnt, overlapPlayerVec);
                    }
                }
                else if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BRICK)
                {
                    if (prevPlayerOverlapVec.y <= 0 && prevPlayerOverlapVec.x > 0) // Entities collided via y-axis i.e. Megaman landing on a block
                    {
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapPlayerVec.y : -overlapPlayerVec.y;
                        if (playerCameFromBottom)
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                        }
                        else
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CInput>().canJump = true;
                            // playerEnt->addComponent<CState>(PlayerStates::STAND);
                        }
                    }
                    else if (prevPlayerOverlapVec.x <= 0 && prevPlayerOverlapVec.y > 0) // Entities collided via x-axis i.e. Megaman running into pipe
                    {
                        playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapPlayerVec.x : -overlapPlayerVec.x;
                    }
                    else if (prevPlayerOverlapVec.x >= 0 && prevPlayerOverlapVec.y >= 0 && overlapPlayerVec.x >= 0 && overlapPlayerVec.y >= 0)
                    {
                        const auto bp = true;
                        // playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapPlayerVec.x : -overlapPlayerVec.x;
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapPlayerVec.y : -overlapPlayerVec.y;

                        if (m_game->debug())
                        {
                            createCollisionTileEntity(m_entityManager, tileEnt);
                        }
                    }
                    else
                    { // // Only when prevOv of x & y are <= 0; So "corner collision" ??
                        const auto bp = true;
                    }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, playerEnt, overlapPlayerVec);
                    }
                }
                else if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::QUESTION)
                {
                    const Vec2 previousOvelap = Physics::GetPreviousOverlap(tileEnt, playerEnt);

                    if (prevPlayerOverlapVec.y <= 0 && prevPlayerOverlapVec.x > 0)
                    {
                        if (playerCameFromBottom)
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CTransform>().pos.y += overlapPlayerVec.y;

                            const CTransform sourceEntTransf = tileEnt->getComponent<CTransform>();
                            const CAnimation sourceEntAni = tileEnt->getComponent<CAnimation>();

                            auto explosEnt = m_entityManager.addEntity(EntityType::DECORATION);
                            CTransform &expEntTransf = explosEnt->addComponent<CTransform>(sourceEntTransf.pos);

                            const auto &exolosionEntAni = explosEnt->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::EXPLOSION), false);
                            const Vec2 explosToSourceRation = getTextureToSizeRatio(exolosionEntAni.animation.getSize(), sourceEntAni.animation.getSize());
                            expEntTransf.scale = explosToSourceRation;

                            explosEnt->addComponent<CLifespan>(exolosionEntAni.animation.getAnimationLifespan(), m_currentFrame, false);
                            tileEnt->destroy();
                        }
                        else
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CTransform>().pos.y -= overlapPlayerVec.y;
                            playerEnt->getComponent<CInput>().canJump = true;
                            // playerEnt->addComponent<CState>(PlayerStates::STAND);
                        }
                    }
                    else if (prevPlayerOverlapVec.x <= 0 && prevPlayerOverlapVec.y > 0)
                    {
                        playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapPlayerVec.x : -overlapPlayerVec.x;
                    }
                    else if (prevPlayerOverlapVec.x >= 0 && prevPlayerOverlapVec.y >= 0 && overlapPlayerVec.x >= 0 && overlapPlayerVec.y >= 0)
                    {
                        const auto bp = true;
                        // playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapPlayerVec.x : -overlapPlayerVec.x;
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapPlayerVec.y : -overlapPlayerVec.y;

                        if (m_game->debug())
                        {
                            createCollisionTileEntity(m_entityManager, tileEnt);
                        }
                    }
                    else
                    { // Only when prevOv of x & y are <= 0; So corner collision ??
                    }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, playerEnt, overlapPlayerVec);
                    }
                }
            }
        }

        /// @brief Check bullets for collisions
        for (auto &bulletEnt : m_entityManager.getEntities(EntityType::BULLET))
        {
            const Vec2 overlapBulletVec = Physics::GetOverlap(tileEnt, bulletEnt);
            if (Physics::IsOverlap(overlapBulletVec))
            {
                bulletEnt->destroy();

                if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BRICK)
                {
                    tileEnt->destroy();
                }

                if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::QUESTION)
                {
                    const CTransform sourceEntTransf = tileEnt->getComponent<CTransform>();
                    const CAnimation sourceEntAni = tileEnt->getComponent<CAnimation>();

                    auto explosEnt = m_entityManager.addEntity(EntityType::DECORATION);
                    CTransform &expEntTransf = explosEnt->addComponent<CTransform>(sourceEntTransf.pos);

                    const auto &exolosionEntAni = explosEnt->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::EXPLOSION), false);
                    const Vec2 explosToSourceRation = getTextureToSizeRatio(exolosionEntAni.animation.getSize(), sourceEntAni.animation.getSize());
                    expEntTransf.scale = explosToSourceRation;

                    explosEnt->addComponent<CLifespan>(exolosionEntAni.animation.getAnimationLifespan(), m_currentFrame, false);

                    tileEnt->destroy();
                }
            }
        }
    }

    /// @brief Check if flag has been touched and if it has fallen to a certain amount to trigger game over
    for (auto &flagEnt : m_entityManager.getEntities(EntityType::FLAG))
    {
        if (flagEnt->hasComponent<CBoundingBox>())
        {
            const Vec2 overlapPlayerVec = Physics::GetOverlap(flagEnt, playerEnt);
            if (flagEnt->getComponent<CAnimation>().animation.getName() == AnimationType::FLAG)
            {
                if (overlapPlayerVec.x > 0 && overlapPlayerVec.y > 0)
                {
                    flagEnt->hasComponent<CGravity>() ? NULL : flagEnt->addComponent<CGravity>(1.5);
                }
            }
        }

        if (flagEnt->hasComponent<CGravity>())
        {
            for (auto &flagPoleEnt : m_entityManager.getEntities(EntityType::FLAG_POLE))
            {
                const float flagPos = flagEnt->getComponent<CTransform>().pos.y;
                const float flagPolePos = flagPoleEnt->getComponent<CTransform>().pos.y;
                const float flagPoleHalfSize = (flagPoleEnt->getComponent<CAnimation>().animation.getSize().y * flagPoleEnt->getComponent<CTransform>().scale.y) / 2;
                const float flagHeight = flagEnt->getComponent<CAnimation>().animation.getSize().y * flagEnt->getComponent<CTransform>().scale.y;
                const float flagHalfSize = flagHeight / 2;

                if (flagPos >= flagPolePos + flagPoleHalfSize - flagHeight - flagHeight / 2)
                {
                    const Vec2 flagPoleOverlap = Physics::GetOverlap(flagEnt, flagPoleEnt);
                    CTransform &flagTransform = flagEnt->getComponent<CTransform>();
                    flagTransform.velocity = Vec2();
                    flagEnt->removeComponent<CGravity>();
                    flagEnt->removeComponent<CBoundingBox>();
                    m_gameOver = true;
                }
            }
        }
    }
}

void Scene_Play::sActions()
{

    for (auto &playerEnt : m_entityManager.getEntities(EntityType::PLAYER))
    {
        if (playerEnt->hasComponent<CActionFrameRecord>())
        {

            auto &playerEntAFR = playerEnt->getComponent<CActionFrameRecord>().actionFrameRecord;
            const auto eOfPlayerAFT = playerEntAFR.end();

            if (playerEntAFR.find(ScenePlayActions::SHOOT) != eOfPlayerAFT && playerEnt->getComponent<CInput>().canShoot && playerEnt->getComponent<CInput>().shoot)
            {
                if (ScenePlayUtil::SHOOT_FRAME_LIMIT <= m_currentFrame - playerEntAFR[ScenePlayActions::SHOOT])
                {
                    spawnBullet(playerEnt);
                    playerEnt->getComponent<CActionFrameRecord>().actionFrameRecord[ScenePlayActions::SHOOT] = m_currentFrame;
                }
            }
        }
    }
}

void Scene_Play::sDoInput(const Action &action)
{
    auto playerEnt = player();
    if (action.type() == ActionType::START)
    {

        if (action.name() == ScenePlayActions::PAUSE)
        {
            setPaused(!m_paused);
        }
        else if (action.name() == ScenePlayActions::TO_MAIN_MENU)
        {
            onEnd();
        }
        else if (action.name() == ScenePlayActions::TOGGLE_TEXTURE)
        {
            m_drawTextures = !m_drawTextures;
        }
        else if (action.name() == ScenePlayActions::TOGGLE_COLLISION)
        {
            m_drawCollision = !m_drawCollision;
        }
        else if (action.name() == ScenePlayActions::TOGGLE_GRID)
        {
            m_drawGrid = !m_drawGrid;
        }
        else if (action.name() == ScenePlayActions::UP)
        {
            playerEnt->getComponent<CInput>().up = true;
        }
        else if (action.name() == ScenePlayActions::LEFT)
        {
            playerEnt->getComponent<CInput>().right = false;
            playerEnt->getComponent<CInput>().left = true;
            playerEnt->getComponent<CState>().state = PlayerStates::RUN;
        }
        else if (action.name() == ScenePlayActions::RIGHT)
        {
            playerEnt->getComponent<CInput>().left = false;
            playerEnt->getComponent<CInput>().right = true;
            playerEnt->getComponent<CState>().state = PlayerStates::RUN;
        }
        else if (action.name() == ScenePlayActions::TO_MAIN_MENU)
        {
            m_game->changeScene();
        }
        else if (action.name() == ScenePlayActions::SHOOT)
        {
            playerEnt->getComponent<CInput>().shoot = true; // For Animation System

            auto playerAFR = playerEnt->getComponent<CActionFrameRecord>().actionFrameRecord; // For Animation System
            if (playerEnt->hasComponent<CActionFrameRecord>())
            {
                if (playerAFR.find(ScenePlayActions::SHOOT) == playerAFR.end())
                {
                    playerEnt->getComponent<CActionFrameRecord>().actionFrameRecord[ScenePlayActions::SHOOT] = SIZE_MAX;
                }
            }
            else
            {
                playerEnt->addComponent<CActionFrameRecord>(ScenePlayActions::SHOOT, SIZE_MAX);
            }
        }
    }
    else if (action.type() == ActionType::END)
    {

        if (action.name() == ScenePlayActions::UP)
        {
            playerEnt->getComponent<CInput>().up = false;
        }
        else if (action.name() == ScenePlayActions::LEFT)
        {
            playerEnt->getComponent<CInput>().left = false;
        }
        else if (action.name() == ScenePlayActions::RIGHT)
        {
            playerEnt->getComponent<CInput>().right = false;
        }
        else if (action.name() == ScenePlayActions::SHOOT)
        {
            playerEnt->getComponent<CInput>().shoot = false;
        }
    }

    if (m_gameOver) {
        if (action.name() == ScenePlayActions::CONTINUE_GAME) {
            m_game->changeScene("SCENE_PLAY", std::make_shared<Scene_Play>(m_game, m_levelPath, m_game->getAssets().getFont("byteSized2")), true);
        }
    }

    if (!playerEnt->getComponent<CInput>().right && !playerEnt->getComponent<CInput>().left &&
        !playerEnt->getComponent<CInput>().up && !playerEnt->getComponent<CInput>().shoot)
    {
        playerEnt->addComponent<CState>().state = PlayerStates::STAND;
    }
}

void Scene_Play::sAnimation()
{
    /// TODO: Complete the Animation class code first

    /// TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
    //          if the animation is not repeated, and it has ended, destroy the entity
    for (auto &entity : m_entityManager.getEntities())
    {
        if (entity->hasComponent<CAnimation>())
        {
            // if (!entity->getComponent<CAnimation>().repeat && entity->getComponent<CAnimation>().animation.hasEnded()) { /// TODO: This or lifespan?
            //     entity->destroy();
            // }
            entity->getComponent<CAnimation>().animation.update();
        }
    }

    // TODO: set the animation of the player based on its CState component
    // if the player's state has been set to running
    const std::string &playerState = player()->getComponent<CState>().state;
    const CInput &playerInput = player()->getComponent<CInput>();
    const std::string playerAnimationName = player()->getComponent<CAnimation>().animation.getName();
    const auto playerAFR = player()->getComponent<CActionFrameRecord>().actionFrameRecord;

    /// TODO: Player state -> Animation map???
    if (!playerInput.shoot)
    {
        if (playerState == PlayerStates::RUN && playerAnimationName != AnimationType::RUN &&
            (playerAFR.find(ScenePlayActions::SHOOT) == playerAFR.end() || ScenePlayUtil::SHOOT_FRAME_LIMIT <= m_currentFrame - playerAFR.at(ScenePlayActions::SHOOT)))
        {
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::RUN), true);
        }
        else if (playerState == PlayerStates::STAND && playerAnimationName != AnimationType::STAND)
        {
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(playerInput.shoot ? AnimationType::STAND_SHOOT : AnimationType::STAND), true);
        }
        else if (playerState == PlayerStates::JUMP && playerAnimationName != AnimationType::JUMP)
        {
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::JUMP), true);
        }
    }
    else
    {
        if (playerState == PlayerStates::RUN && playerAnimationName != AnimationType::RUN_SHOOT)
        {
            std::cout << "Adding Shoot Animation" << std::endl;
            const auto tempAni = m_game->getAssets().getAnimation(AnimationType::RUN_SHOOT);
            const auto tempCAni = CAnimation(tempAni, true);
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::RUN_SHOOT), true);
        }
        else if (playerState == PlayerStates::STAND && playerAnimationName != AnimationType::STAND_SHOOT)
        {
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::STAND_SHOOT), true);
        }
        else if (playerState == PlayerStates::JUMP && playerAnimationName != AnimationType::JUMP_SHOOT)
        {
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::JUMP_SHOOT), true);
        }
    }

    // Reflect Texture so that the texture faces where the player entity is moving
    if (player()->getComponent<CTransform>().velocity.x < 0 && player()->getComponent<CTransform>().scale.x > 0 || player()->getComponent<CTransform>().velocity.x > 0 && player()->getComponent<CTransform>().scale.x < 0)
    {
        player()->getComponent<CTransform>().scale.x *= -1;
    }
}

void Scene_Play::onEnd()
{
    // TODO: When the scene ends, change back to the MENU scene
    //          use m_game.changeScene(correct params);
    m_game->changeScene();
}

void Scene_Play::sRender()
{
    // Color the background darker so you know that the game is paused

    if (!m_paused && !m_gameOver)
    {
        m_game->window().clear(sf::Color(100, 100, 255));
    }
    else
    {
        m_game->window().clear(sf::Color(50, 50, 150));
    }

    // set the viewport of the window to be centered on the play
    auto &pPos = player()->getComponent<CTransform>().pos;

    sf::View view = m_game->window().getView();
    view.setCenter({pPos.x, pPos.y - (m_gridSize.y * 3)});
    m_game->window().setView(view);

    // draw all Entity textures / animations
    if (m_drawTextures)
    {
        for (auto e : m_entityManager.getEntities())
        {
            auto &transform = e->getComponent<CTransform>();

            if (e->hasComponent<CAnimation>())
            {
                auto &animation = e->getComponent<CAnimation>().animation;
                animation.getSprite().setRotation(sf::degrees(transform.angle));
                animation.getSprite().setPosition({transform.pos.x, transform.pos.y});
                animation.getSprite().setScale({transform.scale.x, transform.scale.y});
                m_game->window().draw(animation.getSprite());
            }
        }
    }

    if (m_drawGrid)
    {
        auto tempVari4 = view.getCenter();
        sf::CircleShape circ(10);
        circ.setPosition(view.getCenter());
        circ.setOutlineColor(sf::Color::Red);
        m_game->window().draw(circ);

        sf::Text gridOnText(m_game->getAssets().getFont("byteSized2"), "GRID ON");
        gridOnText.setCharacterSize(20);
        gridOnText.setFillColor(sf::Color::White);
        gridOnText.setPosition({static_cast<float>(view.getCenter().x - view.getSize().x / 2 + m_gridSize.x), view.getCenter().y - view.getSize().y / 2 + m_gridSize.y});
        m_game->window().draw(gridOnText);
        drawGrid();
    }

    // draw all Entity collision bounding boxes with a rectangle
    if (m_drawCollision)
    {
        for (auto e : m_entityManager.getEntities())
        {

            if (e->hasComponent<CBoundingBox>())
            {
                auto &box = e->getComponent<CBoundingBox>();
                auto &transform = e->getComponent<CTransform>();
                sf::RectangleShape rect;

                rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1)); // minus one because of outline thickness?
                rect.setOrigin(sf::Vector2f(box.halfsize.x, box.halfsize.y));
                rect.setPosition({transform.pos.x, transform.pos.y});
                rect.setFillColor(sf::Color(0, 0, 0, 0));
                rect.setOutlineColor((e->tag() != EntityType::COLLISION_VISUAL) ? sf::Color(255, 255, 255, 255) : sf::Color::Red);
                rect.setOutlineThickness(1);
                m_game->window().draw(rect);
            }
        }
    }

    if (m_game->debug())
    {
        auto tempVari = view.getViewport();

        sf::Text debugText(m_game->getAssets().getFont("byteSized2"), "IN DEBUG MODE");
        debugText.setCharacterSize(20);
        debugText.setFillColor(sf::Color::White);
        debugText.setPosition({static_cast<float>(view.getCenter().x - view.getSize().x / 2 + m_gridSize.x), static_cast<float>(view.getCenter().y - view.getSize().y / 2 + m_gridSize.y * 1.5)});
        m_game->window().draw(debugText);
    }

    if (m_gameOver)
    {
        sf::Text gameOverText(m_game->getAssets().getFont("byteSized2"), "GAME OVER\n\nPRESS \'F\' TO CONTINUE");
        gameOverText.setCharacterSize(20);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition({static_cast<float>(view.getCenter().x - view.getSize().x / 2 + m_gridSize.x), view.getCenter().y - view.getSize().y / 2 + m_gridSize.y * 2});
        m_game->window().draw(gameOverText);
    }

    m_game->window().display();
}

/// @brief draws a line between two given points to the window
/// @param p1 point 1
/// @param p2 point 2
void Scene_Play::drawLine(const Vec2 &p1, const Vec2 &p2) const
{
    sf::Vertex line[] = {{sf::Vector2f(p1.x, p1.y)}, {sf::Vector2f(p2.x, p2.y)}};
    m_game->window().draw(line, 2, sf::PrimitiveType::Lines);
}

// Two ways to make it work:
// - Display grid for entire window (so the lines will be completely independent from the view)
// - Display rid for only new what the view sees (The grid "moves" with the view.)

/// @brief  draws a grid (m_gridsize.x X m_gridSize.y) to the game window
void Scene_Play::drawGrid() const
{ /// Significanly drops framerate. Mostlikely need to look at ways to minimize calls to sfml window.draw()
    const sf::Vector2f view_size = m_game->window().getView().getSize();
    sf::Vector2f viewCenter = m_game->window().getView().getCenter();
    const sf::Font coordStringFont = m_gridText.getFont();
    std::ostringstream coordinateString;

    const int viewYDimensionStart = viewCenter.y - view_size.y / 2;
    const float viewToGridYStartOffset = viewYDimensionStart % static_cast<int>(m_gridSize.y);
    const float gridYStartPoint = (viewYDimensionStart - viewToGridYStartOffset);

    const int viewXDimensionStart = viewCenter.x - view_size.x / 2;
    const float tempViewToGridYStartOffset = viewXDimensionStart % static_cast<int>(m_gridSize.x);
    const float gridXStartPoint = (viewXDimensionStart - tempViewToGridYStartOffset);

    const int viewYDimensionEnd = std::abs(viewCenter.y + view_size.y / 2);
    const float viewToGridYOffsetEnd = viewYDimensionEnd % static_cast<int>(m_gridSize.y);
    const float gridYEndPoint = (viewYDimensionEnd - viewToGridYOffsetEnd);

    const int viewXDimensionEnd = std::abs(viewCenter.x + view_size.x / 2);
    const float viewToGridXOffsetEnd = viewXDimensionEnd % static_cast<int>(m_gridSize.x);
    const float gridXEndPoint = (viewXDimensionEnd - viewToGridXOffsetEnd);

    for (float x = gridXStartPoint, y = gridYStartPoint; x <= gridXEndPoint || y <= gridYEndPoint; x += m_gridSize.x, y += m_gridSize.y)
    {
        drawLine({x, viewCenter.y - view_size.y}, {x, viewCenter.y + view_size.y}); // Vertical Lines
        drawLine({viewCenter.x - view_size.x, y}, {viewCenter.x + view_size.x, y}); // Horizontal lines

        for (float j = gridYStartPoint; j <= gridYEndPoint; j += m_gridSize.y)
        {
            // Iterate through each verticle line, and place coordinate at every gridSize worth of distance (This will be where lines intersect)
            coordinateString << "(" << static_cast<int>(x / m_gridSize.y) << "," << static_cast<int>(j / m_gridSize.y) << ")";
            sf::Text coordinateText(coordStringFont, coordinateString.str(), 10);
            coordinateText.setPosition({x, j});
            m_game->window().draw(coordinateText);
            coordinateString.str("");
        }
    }
}

/// @brief returns the player entity (there's only one player for this game)
/// @return  pointer (shared_ptr<Entity>) to the player entity
std::shared_ptr<Entity> Scene_Play::player()
{
    auto &players = m_entityManager.getEntities(EntityType::PLAYER);
    if (players.empty())
    {
        return m_entityManager.addEntity(EntityType::PLAYER);
    }
    return players.at(0);
}

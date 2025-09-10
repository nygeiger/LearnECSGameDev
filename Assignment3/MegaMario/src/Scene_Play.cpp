#include "../headers/Scene_Play.h"
#include "../headers/Physics.h"
#include "../headers/Assets.h"
#include "../headers/GameEngine.h"
#include "../headers/Components.h"
#include "../headers/Action.h"
#include "./Util.cpp"

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
    // registerAction(sf::Keyboard::Scancode::P, ScenePlayActions::PAUSE);
    // registerAction(sf::Keyboard::Scancode::Escape, ScenePlayActions::QUIT);
    // registerAction(sf::Keyboard::Scancode::T, ScenePlayActions::TOGGLE_TEXTURE);
    // registerAction(sf::Keyboard::Scancode::C, ScenePlayActions::TOGGLE_COLLISION);
    // registerAction(sf::Keyboard::Scancode::G, ScenePlayActions::TOGGLE_GRID);
    registerAction(sf::Keyboard::Scancode::P, ScenePlayActions::PAUSE);
    registerAction(sf::Keyboard::Scancode::Escape, ScenePlayActions::TO_MAIN_MENU);
    registerAction(sf::Keyboard::Scancode::T, ScenePlayActions::TOGGLE_TEXTURE);
    registerAction(sf::Keyboard::Scancode::C, ScenePlayActions::TOGGLE_COLLISION);
    registerAction(sf::Keyboard::Scancode::G, ScenePlayActions::TOGGLE_GRID);

    // TODO: Register all other gameplay Actions
    // registerAction(sf::Keyboard::Scancode::W, ScenePlayActions::UP);
    registerAction(sf::Keyboard::Scancode::W, ScenePlayActions::UP);
    registerAction(sf::Keyboard::Scancode::A, ScenePlayActions::LEFT);
    registerAction(sf::Keyboard::Scancode::D, ScenePlayActions::RIGHT);

    m_gridText.setCharacterSize(12);
    // m_gridText.setFont(m_game->assets.getFont("Tech"));
    // m_gridText.setFont(m_game->m_assets.getFont("Tech"));

    loadLevel(levelPath);
}

// void readLevelFromFile(const std::string& fileName) {
//  std::ifstream file(fileName);
//     std::string lineHeader;
//     if (file.bad()) {std::cerr << "FAILED to load level file: " << fileName << std::endl;}

//     while (file.good())
//     {
//         file >> lineHeader;

//         if (lineHeader == "Tile") {
//             std::string animationName;
//             /*size_t*/ int gx, gy;
//             file >> animationName >> gx >> gy;
//             const bool bp = true;

//             auto tile =
//         }
//     }
// }

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

        if (lineHeader == "Tile")
        {
            std::string animationName;
            /*size_t*/ int gx, gy;
            file >> animationName >> gx >> gy;
            const bool bp = true;
            auto tile = m_entityManager.addEntity(EntityType::TILE);
            tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(animationName), false);
            tile->addComponent<CTransform>(Vec2((gx * m_gridSize.x) + m_gridSize.x / 2, (gy * m_gridSize.y) - m_gridSize.y / 2));

            const Vec2 textureSize = tile->getComponent<CAnimation>().animation.getSize();
            const Vec2 textToGridBlockRatio = {m_gridSize.x / textureSize.x, m_gridSize.y / textureSize.y};
            tile->getComponent<CTransform>().scale = textToGridBlockRatio;
            tile->addComponent<CBoundingBox>(textureSize * textToGridBlockRatio);
        }
    }

    //  Note:   all of the code below is sample code which shows you how to set up
    //          and use entities with the new syntax, it should be removed

    spawnPlayer();

    // some sample entities
    auto brick = m_entityManager.addEntity(EntityType::TILE);
    // IMPORTANT: always add the CAnimation compnent first so that gridToMidPixel can compute correctly
    brick->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::BRICK), true);
    auto tempVari = brick->getComponent<CAnimation>().animation.m_sprite.getScale();
    brick->addComponent<CTransform>(Vec2(96, 480));

    // NOTE: Your final code should position the entity with the grid x,y position read from the file:
    // brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick));

    if (brick->getComponent<CAnimation>().animation.getName() == AnimationType::BRICK)
    {
        std::cout << "This could be a good way of identifying if a tile is a brick" << std::endl;
    }

    auto block = m_entityManager.addEntity(EntityType::TILE);
    block->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::BLOCK), true);
    block->addComponent<CTransform>(Vec2(224, 48));
    const Vec2 currentBlockSize = block->getComponent<CAnimation>().animation.getSize();
    const Vec2 textToWindowSizeFactor = {m_game->window().getSize().x / currentBlockSize.x, m_game->window().getSize().y / currentBlockSize.y};
    const int blockToWindowSizeRatio = 12; // blocks are 1/12 of window size
    block->getComponent<CAnimation>().animation.getSprite().setScale({(currentBlockSize.x * textToWindowSizeFactor.x) / blockToWindowSizeRatio, (currentBlockSize.y * textToWindowSizeFactor.y) / blockToWindowSizeRatio});
    // add bounding box, this will now show up if we press the 'C' key
    // block->addComponent<CBoundingBox>(m_game->getAssets().getAnimation(AnimationType::BLOCK).getSize());
    const auto tempVari2 = block->getComponent<CAnimation>().animation.getSize();
    const auto tempVari3 = m_game->getAssets().getAnimation(AnimationType::BLOCK).getSize();
    block->addComponent<CBoundingBox>(block->getComponent<CAnimation>().animation.getSize());

    auto question = m_entityManager.addEntity(EntityType::TILE);
    question->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::QUESTION), true);
    question->addComponent<CTransform>(Vec2(352, 480));
    const Vec2 questionTextureSize = question->getComponent<CAnimation>().animation.getSize();
    const Vec2 questionTextToGridBlockRatio = {m_gridSize.x / questionTextureSize.x, m_gridSize.y / questionTextureSize.y};
    question->getComponent<CTransform>().scale = questionTextToGridBlockRatio;
    question->addComponent<CBoundingBox>(questionTextureSize * questionTextToGridBlockRatio);
    const auto tempVari4 = questionTextureSize * questionTextToGridBlockRatio;
    const bool bp = true;

    // NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
    /* Components are now returned as refrences rather than pointers
        If you do not specify a reference varibale type, it will COPY the component
        Here's an example:

        This will COPY the transform into the variable 'transform1' - it is INCORRECT
        Any changes you make to transform1 will not be changed inside the entity
        auto transform1 = entity->get<cTransform>()

        This will REFRENCE the transform with the variable 'transform2' - it is CORRECT
        Now any changes you make to transform2 will be changed inside the entity
        auto& transform2 = entity->get<CTransform>()

    */

    // readLevelFromFile(fileName);
}

void Scene_Play::spawnPlayer()
{
    // here is a sple player enity which you can use to construct other entities

    m_player = m_entityManager.addEntity(EntityType::PLAYER);
    m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::STAND), true);
    // m_player->addComponent<CTransform>(Vec2(224, 352));
    m_player->addComponent<CTransform>(Vec2(1280 / 2, 768 / 2));
    m_player->addComponent<CBoundingBox>(Vec2(48, 48));
    m_player->addComponent<CState>("STAND");
    m_player->addComponent<CInput>();
    m_player->addComponent<CGravity>(1);

    // TODO: be sure to addd the remaining components to the palyer
    // be sure to destroy the dead player if you're respawning
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
    // TODO: this should spawn a bullet at (from) the given entity, going in the direction the entitu is facing
}

void Scene_Play::update()
{
    m_entityManager.update();

    if (!m_paused)
    {
        sMovement();
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
}

void Scene_Play::sMovement()
{
    // TODO: Implement player movement / jumpinng based onn its CInput component
    // TODO: Implement gravity's effect on the player
    // TODO: Implement the maximum player speed in both x and y directions
    // NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right

    const float MaxSpeed = 7.0f;
    const float MaxSpeedInv = MaxSpeed * -1;
    const float runSpeed = 1.75;

    auto &playerInput = m_player->getComponent<CInput>();

    if (playerInput.left)
    {
        m_player->getComponent<CTransform>().velocity.x = -runSpeed;
    }
    else if (playerInput.right)
    {
        m_player->getComponent<CTransform>().velocity.x = runSpeed;
    }
    else
    {
        m_player->getComponent<CTransform>().velocity.x = 0;
    }

    Vec2 playerVelocity(m_player->getComponent<CTransform>().velocity.x, m_player->getComponent<CTransform>().velocity.y);
    if (playerInput.canJump && playerInput.up)
    {
        m_player->getComponent<CTransform>().velocity.y -= 30; // Delete "playerVelocity" Vec2 and just do this?
        auto &playerInput = m_player->getComponent<CInput>().canJump = false;
        m_player->addComponent<CState>(PlayerStates::JUMP);
        m_player->addComponent<CGravity>(1);
    }

    // m_player->getComponent<CTransform>().velocity = playerVelocity;

    for (auto e : m_entityManager.getEntities())
    {
        if (e->hasComponent<CGravity>())
        {
            e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
            // if player is moving faster than max speed in any direction
            // set the speed of the player to the max

            if (e->getComponent<CTransform>().velocity.y > MaxSpeed)
            {
                e->getComponent<CTransform>().velocity.y = MaxSpeed;
            }
            if (e->getComponent<CTransform>().velocity.x > MaxSpeed)
            {
                e->getComponent<CTransform>().velocity.x = MaxSpeed;
            }
            if (e->getComponent<CTransform>().velocity.y < MaxSpeedInv)
            {
                e->getComponent<CTransform>().velocity.y = MaxSpeedInv;
            }
            if (e->getComponent<CTransform>().velocity.x < MaxSpeedInv)
            {
                e->getComponent<CTransform>().velocity.x = MaxSpeedInv;
            }

            // reset down velocity to 0 when touching the ground
        }
        e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;
        e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
    }
}

void Scene_Play::sLifespan()
{
}

/**
 * Helper function only used to help debug during collision development
 *currently only works with one moving and one stationary object
 */
void createCollisionAreaEntity(EntityManager &entityManager, const bool &playerCameFromRight, const bool &playerCameFromBottom, std::shared_ptr<Entity> movingEnt, const Vec2 &overlapVec)
{
    // auto collisionVisualEnt = m_entityManager.addEntity(EntityType::COLLISION_VISUAL);
    // // tempEnt->addComponent<CTransform>(tileEnt->getComponent<CTransform>().pos);
    // const float collVisXPoint = (playerCameFromRight) ? m_player->getComponent<CTransform>().pos.x - m_player->getComponent<CBoundingBox>().halfsize.x : m_player->getComponent<CTransform>().pos.x + m_player->getComponent<CBoundingBox>().halfsize.x;
    // const float collVisYPoint = (playerCameFromBottom) ? m_player->getComponent<CTransform>().pos.y - m_player->getComponent<CBoundingBox>().halfsize.y : m_player->getComponent<CTransform>().pos.y + m_player->getComponent<CBoundingBox>().halfsize.y;

    //     collisionVisualEnt->addComponent<CTransform>(Vec2(collVisXPoint, collVisYPoint));
    //     collisionVisualEnt->addComponent<CBoundingBox>(overlapVec);

    auto collisionVisualEnt = entityManager.addEntity(EntityType::COLLISION_VISUAL);
    // tempEnt->addComponent<CTransform>(tileEnt->getComponent<CTransform>().pos);
    const float collVisXPoint = (playerCameFromRight) ? movingEnt->getComponent<CTransform>().pos.x - movingEnt->getComponent<CBoundingBox>().halfsize.x : movingEnt->getComponent<CTransform>().pos.x + movingEnt->getComponent<CBoundingBox>().halfsize.x;
    // const float collVisXPoint = (playerCameFromRight) ? movingEnt->getComponent<CTransform>().pos.x - movingEnt->getComponent<CBoundingBox>().halfsize.x : (movingEnt->getComponent<CTransform>().pos.x == movingEnt->getComponent<CTransform>().prevPos.x) ? movingEnt->getComponent<CTransform>().pos.x : movingEnt->getComponent<CTransform>().pos.x + movingEnt->getComponent<CBoundingBox>().halfsize.x;
    const float collVisYPoint = (playerCameFromBottom) ? movingEnt->getComponent<CTransform>().pos.y - movingEnt->getComponent<CBoundingBox>().halfsize.y : movingEnt->getComponent<CTransform>().pos.y + movingEnt->getComponent<CBoundingBox>().halfsize.y;
    collisionVisualEnt->addComponent<CTransform>(Vec2(collVisXPoint, collVisYPoint));
    collisionVisualEnt->addComponent<CBoundingBox>(overlapVec);
}

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
    for (auto &tileEnt : m_entityManager.getEntities(EntityType::TILE))
    {
        if (tileEnt->hasComponent<CBoundingBox>())
        {
            const Vec2 overlapVec = Physics::GetOverlap(tileEnt, m_player);
            if (Physics::IsOverlap(overlapVec))
            {
                const Vec2 prevOverlapVec = Physics::GetPreviousOverlap(tileEnt, m_player);
                CTransform playerTrans = m_player->getComponent<CTransform>();
                CBoundingBox playerBBox = m_player->getComponent<CBoundingBox>();

                /// TODO: Use these or velocity???
                const bool playerCameFromRight = m_player->getComponent<CTransform>().prevPos.x > m_player->getComponent<CTransform>().pos.x;
                const bool playerCameFromBottom = m_player->getComponent<CTransform>().prevPos.y > m_player->getComponent<CTransform>().pos.y;

                if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BLOCK)
                {
                    if (prevOverlapVec.y <= 0 && prevOverlapVec.x > 0) // Entities collided via y-axis i.e. Megaman landing on a block
                    {
                        m_player->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapVec.y : -overlapVec.y;
                        if (playerCameFromBottom)
                        {
                            m_player->getComponent<CTransform>().velocity.y = 0;
                        }
                        else
                        {
                            m_player->getComponent<CTransform>().velocity.y = 0;
                            m_player->getComponent<CInput>().canJump = true;
                            // m_player->removeComponent<CGravity>();
                        }
                    }
                    else if (prevOverlapVec.x <= 0 && prevOverlapVec.y > 0) // Entities collided via x-axis i.e. Megaman running into pipe
                    {
                        m_player->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                        // m_player->getComponent<CTransform>().pos.x += (m_player->getComponent<CTransform>().velocity.x < 0) ? overlapVec.x : -overlapVec.x;
                    } else { // // Only when prevOv of x & y are <= 0; So "corner collision" ??

                    }

                    // const auto tempXCollisThreshold = m_player->getComponent<CBoundingBox>().size.x / 100;
                    // if (overlapVec.x > overlapVec.y) // Entities collided via y-axis i.e. Megaman landing on a block
                    // {
                    //     m_player->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapVec.y : -overlapVec.y;
                    //     if (playerCameFromBottom)
                    //     {
                    //         m_player->getComponent<CTransform>().velocity.y = 0;
                    //     }
                    //     else
                    //     {
                    //         m_player->getComponent<CTransform>().velocity.y = 0;
                    //         // m_player->removeComponent<CGravity>();
                    //     }
                    // }
                    // else if (overlapVec.y > overlapVec.x && (overlapVec.x - m_player->getComponent<CBoundingBox>().size.x > 5)) // Entities collided via x-axis i.e. Megaman running into pipe
                    // {
                    //     m_player->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                    //     // m_player->getComponent<CTransform>().pos.x += (m_player->getComponent<CTransform>().velocity.x < 0) ? overlapVec.x : -overlapVec.x;
                    // }
                    /**
                     * ##### Attempts to detect and handle "Corner Collision" cases #####
                     */
                    // else if ((overlapVec.x < m_player->getComponent<CBoundingBox>().size.x && overlapVec.y < m_player->getComponent<CBoundingBox>().size.y) || (overlapVec.x < tileEnt->getComponent<CBoundingBox>().size.x && overlapVec.y < tileEnt->getComponent<CBoundingBox>().size.y)) {
                    //     const auto bp2 = true;
                    // }
                    // else
                    // {
                    //     const bool bp = true;
                    //     if (prevOverlapVec.y <= 0)
                    //     {
                    //         m_player->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapVec.y : -overlapVec.y;
                    //     }
                    //     else if (prevOverlapVec.x <= 0)
                    //     {
                    //         m_player->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                    //     }
                    // }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, m_player, overlapVec);
                    }
                }
                else if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BRICK)
                {
                    tileEnt->destroy();
                    m_player->addComponent<CGravity>(1);
                }
                else if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::QUESTION)
                {
                    const Vec2 previousOvelap = Physics::GetPreviousOverlap(tileEnt, m_player);

                    if (prevOverlapVec.y <= 0 && prevOverlapVec.x > 0)
                    {
                        if (playerCameFromBottom)
                        {
                            tileEnt->destroy();
                            m_player->getComponent<CTransform>().velocity.y = 0;
                            m_player->getComponent<CTransform>().pos.y += overlapVec.y;
                        }
                        else
                        {
                            m_player->getComponent<CTransform>().velocity.y = 0;
                            m_player->getComponent<CTransform>().pos.y -= overlapVec.y;
                            m_player->getComponent<CInput>().canJump = true;
                        }
                    }
                    else if (prevOverlapVec.x <= 0 && prevOverlapVec.y > 0)
                    {
                        m_player->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                    }
                    else
                    { // Only when prevOv of x & y are <= 0; So corner collision ??
                    }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, m_player, overlapVec);
                    }
                }
            }
        }
    }

    // TODO: Check to see if the player has fallen down a hole (y > height())

    // TODO: Don't let the player walk off the left side of the map
}

void Scene_Play::sDoAction(const Action &action)
{
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
            m_player->getComponent<CInput>().up = true;
        }
        else if (action.name() == ScenePlayActions::LEFT)
        {
            m_player->getComponent<CInput>().right = false;
            m_player->getComponent<CInput>().left = true;
            m_player->getComponent<CState>().state = PlayerStates::RUN;
        }
        else if (action.name() == ScenePlayActions::RIGHT)
        {
            m_player->getComponent<CInput>().left = false;
            m_player->getComponent<CInput>().right = true;
            m_player->getComponent<CState>().state = PlayerStates::RUN;
        }
        else if (action.name() == ScenePlayActions::TO_MAIN_MENU)
        {
            m_game->changeScene();
        }
    }
    else if (action.type() == ActionType::END)
    {

        if (action.name() == ScenePlayActions::UP)
        {
            m_player->getComponent<CInput>().up = false;
        }
        else if (action.name() == ScenePlayActions::LEFT)
        {
            m_player->getComponent<CInput>().left = false;
        }
        else if (action.name() == ScenePlayActions::RIGHT)
        {
            m_player->getComponent<CInput>().right = false;
        }

        // TODO: Goes here? Maybe in sMovement?
        // TODO: Is this the best way to reset state to defualt?
        if (!m_player->getComponent<CInput>().right && !m_player->getComponent<CInput>().left &&
            !m_player->getComponent<CInput>().up && !m_player->getComponent<CInput>().shoot)
        {
            m_player->addComponent<CState>().state = PlayerStates::STAND;
        }
    }
}

void Scene_Play::sAnimation()
{
    // TODO: Complete the Animation class code first

    // TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
    //          if the animation is not repeated, and it has ended, destroy the entity
    for (auto &entity : m_entityManager.getEntities())
    {
        if (entity->hasComponent<CAnimation>())
        {
            entity->getComponent<CAnimation>().animation.update();
        }
    }

    // TODO: set the animation of the player based on its CState component
    // if the player's state has been set to running
    const CState &playerState = player()->getComponent<CState>();
    const std::string playerAnimationName = player()->getComponent<CAnimation>().animation.getName();

    /// TODO: Player state -> Animation map???
    if (playerState.state == PlayerStates::RUN)
    {
        if (playerAnimationName != AnimationType::RUN)
        {
            player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::RUN), true);
        }
    }
    else if (playerState.state == PlayerStates::STAND && playerAnimationName != AnimationType::STAND)
    {
        player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::STAND), true);
    }
    else if (playerState.state == PlayerStates::JUMP && playerAnimationName != AnimationType::JUMP)
    {
        player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::JUMP), true);
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
    // m_game->changeScene("playScene", std::make_shared<Scene_Menu>(m_game, sf::Font()), true);
    // m_game->changeScene("scene_play", std::make_shared<Scene_Menu>(sf::Font()));
    m_game->changeScene();
}

// void Scene_Play::sGUI() {
//     ImGui::Begin("Scene Properties");

//     if(ImGui::BeginTabBar("MyTabBar")) {
//         if (ImGui::BeginTabItem("Actions")) {
//             for (const auto& [key, name] : getActionmap()) {
//                 std::string ss = "START##" + name;
//                 std::string se = "END##" + name;

//                 if (ImGui::Button(ss.c_str())) {
//                     doAction(Action(name, "START"));
//                 }
//                 ImGui::SameLine();
//                 if (ImGui::Button(se.c_str())) {
//                     doAction(Action(name, "END"));
//                 }
//                 ImGui::SameLine();
//                 ImGui::Text("%s", name.c_str());
//             }
//             ImGui::EndTabItem();
//         }

//         if (ImGui::BeginTabItem("Assets")) {
//             if (ImGui::CollapsingHeader("Animations", ImGuiTreeNode)) {
//                 ImGui::Indent();
//                 int count = 0;
//                 for (const auto& [name, anim] : m_game.assets().) {
//                     count++;
//                     ImGui::ImageButton(((Animation)anim).getSprite())
//                     if ((count % 6) !- 0 && count != m_game.assets)
//                 }
//                 Im::GuiUnindent();
//             }
//             ImGui::EndTabItem();
//         }
//         ImGui::EndTabBar();
//     }
//     ImGui::End();
// }

void Scene_Play::sRender()
{
    // Color the background darker so you know that the game is paused

    if (!m_paused)
    {
        m_game->window().clear(sf::Color(100, 100, 255));
    }
    else
    {
        m_game->window().clear(sf::Color(50, 50, 150));
    }

    // // set the viewport of the window to be centered on the play
    // auto &pPos = player()->getComponent<CTransform>().pos;
    // // float windowCenterX = std::max(m_game->window().getSize().x /);
    // float windowCenterX = std::max((int)m_game->window().getSize().x / 2, 90);

    // sf::View view = m_game->window().getView();
    // // view.setCenter(windowCenterX, m_game.window().getSize().y - );
    // view.setCenter({windowCenterX, static_cast<float>(m_game->window().getSize().y)});
    // m_game->window().setView(view);

    // draw all Entity textures / animations
    if (m_drawTextures)
    {
        for (auto e : m_entityManager.getEntities())
        {
            auto &transform = e->getComponent<CTransform>();

            if (e->hasComponent<CAnimation>())
            {
                auto &animation = e->getComponent<CAnimation>().animation;
                // animation.update();
                animation.getSprite().setRotation(sf::degrees(transform.angle));
                animation.getSprite().setPosition({transform.pos.x, transform.pos.y});
                animation.getSprite().setScale({transform.scale.x, transform.scale.y});
                m_game->window().draw(animation.getSprite());
                // animation.update();
            }
        }
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

                rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1)); // minues one because of outline thickness?
                rect.setOrigin(sf::Vector2f(box.halfsize.x, box.halfsize.y));
                rect.setPosition({transform.pos.x, transform.pos.y});
                rect.setFillColor(sf::Color(0, 0, 0, 0));
                rect.setOutlineColor((e->tag() != EntityType::COLLISION_VISUAL) ? sf::Color(255, 255, 255, 255) : sf::Color::Red);
                rect.setOutlineThickness(1);
                m_game->window().draw(rect);
            }
        }
    }

    if (m_drawGrid)
    {
        drawGrid();
    }

    if (m_game->debug())
    {
        sf::Text debugText(m_game->getAssets().getFont("byteSized2"), "IN DEBUG MODE");
        debugText.setCharacterSize(20);
        debugText.setFillColor(sf::Color::White);
        debugText.setPosition({static_cast<float>(m_game->window().getSize().x / 2), 32});
        m_game->window().draw(debugText);
    }

    m_game->window().display();
}

void Scene_Play::drawLine(const Vec2 &p1, const Vec2 &p2) const
{
    sf::Vertex line[] = {{sf::Vector2f(p1.x, p1.y)}, {sf::Vector2f(p2.x, p2.y)}};
    m_game->window().draw(line, 2, sf::PrimitiveType::Lines);
}

void Scene_Play::drawGrid() const
{ /// Significanly drops framerate. Mostlikely need to look at ways to minimize calls to sfml window.draw()

    const sf::Vector2u window_size = m_game->window().getSize();
    const int gridBlockSize = 64;
    const int maxGridLines = window_size.x > window_size.y ? window_size.x / gridBlockSize : window_size.y / gridBlockSize;
    const int numVerticleLinePoints = window_size.x / gridBlockSize;
    const sf::Font coordStringFont = m_gridText.getFont(); // Heavily reduced lag. Current Temporary fix

    for (float i = 1; i < maxGridLines; i++)
    {
        drawLine({i * gridBlockSize, 0}, {i * 64, static_cast<float>(window_size.y)});
        drawLine({0, i * gridBlockSize}, {static_cast<float>(window_size.x), i * gridBlockSize});

        for (float j = 0; j < numVerticleLinePoints; j++)
        {

            std::ostringstream coordinateString;
            coordinateString << "( " << i << ", " << j << ")";

            // const sf::Font coordStringFont = m_gridText.getFont();
            sf::Text coordinateText(coordStringFont, coordinateString.str(), 10);

            coordinateText.setPosition({i * gridBlockSize, j * gridBlockSize});
            m_game->window().draw(coordinateText);
        }
    }
}

std::shared_ptr<Entity> Scene_Play::player()
{
    auto &players = m_entityManager.getEntities(EntityType::PLAYER);
    if (players.empty())
    {
        return m_entityManager.addEntity(EntityType::PLAYER);
    }
    return players.at(0);
}

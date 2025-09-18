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

    // TODO: Register all other gameplay Actions
    registerAction(sf::Keyboard::Scancode::W, ScenePlayActions::UP);
    registerAction(sf::Keyboard::Scancode::A, ScenePlayActions::LEFT);
    registerAction(sf::Keyboard::Scancode::D, ScenePlayActions::RIGHT);

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
        if (lineHeader == "Question")
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
    // IMPORTANT: always add the CAnimation compnent first so that gridToMidPixel can compute correctly

    // NOTE: Your final code should position the entity with the grid x,y position read from the file:
    // brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick));

    // auto question = m_entityManager.addEntity(EntityType::TILE);
    // question->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::QUESTION), true);
    // question->addComponent<CTransform>(Vec2(352, 480));
    // const Vec2 questionTextureSize = question->getComponent<CAnimation>().animation.getSize();
    // const Vec2 questionTextToGridBlockRatio = {m_gridSize.x / questionTextureSize.x, m_gridSize.y / questionTextureSize.y};
    // question->getComponent<CTransform>().scale = questionTextToGridBlockRatio;
    // question->addComponent<CBoundingBox>(questionTextureSize * questionTextToGridBlockRatio);
    // const auto tempVari4 = questionTextureSize * questionTextToGridBlockRatio;
    // const bool bp = true;

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
    std::shared_ptr<Entity> playerEnt = player();
    playerEnt->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::STAND), true);
    playerEnt->addComponent<CTransform>(Vec2(m_game->window().getDefaultView().getCenter().x, m_game->window().getDefaultView().getCenter().y));
    playerEnt->addComponent<CBoundingBox>((playerEnt->getComponent<CAnimation>().animation.getSize() - Vec2(16, 16)));
    playerEnt->addComponent<CState>("STAND");
    playerEnt->addComponent<CInput>();
    playerEnt->addComponent<CGravity>(1);

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

    const float playerLowestPoint = 12 * m_gridSize.y;

    const float xMaxSpeed = 7.0f;
    const float xMaxSpeedInv = xMaxSpeed * -1;
    const float yMaxSpeed = 25.0f;
    const float yMaxSpeedInv = yMaxSpeed * -1;
    const float runSpeed = 4.75;

    // auto playerEnt = player();
    // auto &playerInput = playerEnt->getComponent<CInput>();
    // auto &playerPos = playerEnt->getComponent<CTransform>().pos;

    /// TODO: Move player logic into entMan loop? Since different entities may need cust logic it'd be the logical place to be
    // if (playerInput.left)
    // {
    //     playerEnt->getComponent<CTransform>().velocity.x = -runSpeed;
    // }
    // else if (playerInput.right)
    // {
    //     playerEnt->getComponent<CTransform>().velocity.x = runSpeed;
    // }
    // else
    // {
    //     playerEnt->getComponent<CTransform>().velocity.x = 0;
    // }

    // if (playerInput.canJump && playerInput.up)
    // {
    //     playerEnt->getComponent<CTransform>().velocity.y -= 17; // Delete "playerVelocity" Vec2 and just do this?
    //     auto &playerInput = playerEnt->getComponent<CInput>().canJump = false;
    //     playerEnt->addComponent<CState>(PlayerStates::JUMP);
    //     playerEnt->addComponent<CGravity>(1);
    // }

    // if (playerPos.y > playerLowestPoint) {
    //     playerEnt->addComponent<CTransform>(Vec2(m_game->window().getDefaultView().getCenter().x, m_game->window().getDefaultView().getCenter().y));
    // }

    // if (playerPos.x - playerEnt->getComponent<CTransform>().velocity.x <= 0 &&  playerEnt->getComponent<CTransform>().velocity.x < 0) {
    //     playerEnt->getComponent<CTransform>().velocity.x = 0;
    // }

    for (auto e : m_entityManager.getEntities())
    {
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
                e->getComponent<CTransform>().velocity.y -= 17; // Delete "playerVelocity" Vec2 and just do this?
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
        }
        if (e->hasComponent<CGravity>())
        {
            e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
            // if player is moving faster than max speed in any direction
            // set the speed of the player to the max

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
    auto collisionVisualEnt = entityManager.addEntity(EntityType::COLLISION_VISUAL);
    const float collVisXPoint = (playerCameFromRight) ? movingEnt->getComponent<CTransform>().pos.x - movingEnt->getComponent<CBoundingBox>().halfsize.x : movingEnt->getComponent<CTransform>().pos.x + movingEnt->getComponent<CBoundingBox>().halfsize.x;
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
    auto playerEnt = player();
    for (auto &tileEnt : m_entityManager.getEntities(EntityType::TILE))
    {
        if (tileEnt->hasComponent<CBoundingBox>())
        {
            // const Vec2 overlapVec = Physics::GetOverlap(tileEnt, m_player);
            const Vec2 overlapVec = Physics::GetOverlap(tileEnt, playerEnt);
            if (Physics::IsOverlap(overlapVec))
            {
                const Vec2 prevOverlapVec = Physics::GetPreviousOverlap(tileEnt, playerEnt);
                CTransform playerTrans = playerEnt->getComponent<CTransform>();
                CBoundingBox playerBBox = playerEnt->getComponent<CBoundingBox>();

                /// TODO: Use these or velocity???
                const bool playerCameFromRight = playerEnt->getComponent<CTransform>().prevPos.x > playerEnt->getComponent<CTransform>().pos.x;
                const bool playerCameFromBottom = playerEnt->getComponent<CTransform>().prevPos.y > playerEnt->getComponent<CTransform>().pos.y;

                if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BLOCK)
                {
                    if (prevOverlapVec.y <= 0 && prevOverlapVec.x > 0) // Entities collided via y-axis i.e. Megaman landing on a block
                    {
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapVec.y : -overlapVec.y;
                        if (playerCameFromBottom)
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                        }
                        else
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CInput>().canJump = true;
                            if (!Physics::IsOverlap(prevOverlapVec)) playerEnt->addComponent<CState>(playerEnt->getComponent<CInput>().left || playerEnt->getComponent<CInput>().right ? PlayerStates::RUN : PlayerStates::STAND);
                        }
                    }
                    else if (prevOverlapVec.x <= 0 && prevOverlapVec.y > 0) // Entities collided via x-axis i.e. Megaman running into pipe
                    {
                        playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                    }
                    else
                    { // // Only when prevOv of x & y are <= 0; So "corner collision" ??
                    }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, playerEnt, overlapVec);
                    }
                }
                else if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::BRICK)
                {
                    if (prevOverlapVec.y <= 0 && prevOverlapVec.x > 0) // Entities collided via y-axis i.e. Megaman landing on a block
                    {
                        playerEnt->getComponent<CTransform>().pos.y += (playerCameFromBottom) ? overlapVec.y : -overlapVec.y;
                        if (playerCameFromBottom)
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                        }
                        else
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CInput>().canJump = true;
                            playerEnt->addComponent<CState>(PlayerStates::STAND);
                        }
                    }
                    else if (prevOverlapVec.x <= 0 && prevOverlapVec.y > 0) // Entities collided via x-axis i.e. Megaman running into pipe
                    {
                        playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                    }
                    else
                    { // // Only when prevOv of x & y are <= 0; So "corner collision" ??
                    }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, playerEnt, overlapVec);
                    }
                }
                else if (tileEnt->getComponent<CAnimation>().animation.getName() == AnimationType::QUESTION)
                {
                    const Vec2 previousOvelap = Physics::GetPreviousOverlap(tileEnt, playerEnt);

                    if (prevOverlapVec.y <= 0 && prevOverlapVec.x > 0)
                    {
                        if (playerCameFromBottom)
                        {
                            tileEnt->destroy();
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CTransform>().pos.y += overlapVec.y;
                        }
                        else
                        {
                            playerEnt->getComponent<CTransform>().velocity.y = 0;
                            playerEnt->getComponent<CTransform>().pos.y -= overlapVec.y;
                            playerEnt->getComponent<CInput>().canJump = true;
                            playerEnt->addComponent<CState>(PlayerStates::STAND);
                        }
                    }
                    else if (prevOverlapVec.x <= 0 && prevOverlapVec.y > 0)
                    {
                        playerEnt->getComponent<CTransform>().pos.x += (playerCameFromRight) ? overlapVec.x : -overlapVec.x;
                    }
                    else
                    { // Only when prevOv of x & y are <= 0; So corner collision ??
                    }

                    if (m_game->debug())
                    {
                        createCollisionAreaEntity(m_entityManager, playerCameFromRight, playerCameFromBottom, playerEnt, overlapVec);
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

        // TODO: Goes here? Maybe in sMovement?
        // TODO: Is this the best way to reset state to defualt?
        if (!playerEnt->getComponent<CInput>().right && !playerEnt->getComponent<CInput>().left &&
            !playerEnt->getComponent<CInput>().up && !playerEnt->getComponent<CInput>().shoot)
        {
            playerEnt->addComponent<CState>().state = PlayerStates::STAND;
        }
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
            entity->getComponent<CAnimation>().animation.update();
        }
    }

    // TODO: set the animation of the player based on its CState component
    // if the player's state has been set to running
    const CState &playerState = player()->getComponent<CState>();
    const std::string playerAnimationName = player()->getComponent<CAnimation>().animation.getName();

    /// TODO: Player state -> Animation map???
    if (playerState.state == PlayerStates::RUN && playerAnimationName != AnimationType::RUN)
    {
        player()->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::RUN), true);
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

    if (m_game->debug())
    {
        auto tempVari = view.getViewport();

        sf::Text debugText(m_game->getAssets().getFont("byteSized2"), "IN DEBUG MODE");
        debugText.setCharacterSize(20);
        debugText.setFillColor(sf::Color::White);
        debugText.setPosition({static_cast<float>(view.getCenter().x - view.getSize().x / 2 + m_gridSize.x), view.getCenter().y - view.getSize().y / 2 + m_gridSize.y * 2});
        m_game->window().draw(debugText);
    }

    m_game->window().display();
}

void Scene_Play::drawLine(const Vec2 &p1, const Vec2 &p2) const
{
    sf::Vertex line[] = {{sf::Vector2f(p1.x, p1.y)}, {sf::Vector2f(p2.x, p2.y)}};
    m_game->window().draw(line, 2, sf::PrimitiveType::Lines);
}

// Two ways to make it work:
// - Display grid for entire window (so the lines will be completely independent from the view)
// - Display rid for only new what the view sees (The grid "moves" with the view.)
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

std::shared_ptr<Entity> Scene_Play::player()
{
    auto &players = m_entityManager.getEntities(EntityType::PLAYER);
    if (players.empty())
    {
        return m_entityManager.addEntity(EntityType::PLAYER);
    }
    return players.at(0);
}

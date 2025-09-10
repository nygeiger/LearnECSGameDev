#include "../headers/Scene_Menu.h"
#include "../headers/Scene_Play.h"
#include "../headers/Assets.h"
#include "../headers/GameEngine.h"
#include "../headers/Components.h"
#include "../headers/Action.h"
#include "./Util.cpp"

#include <sstream>

// Scene_Menu::Scene_Menu(GameEngine& gameEngine) : Scene(gameEngine)  {
//     init();
// },,,,,,,,,,,
Scene_Menu::Scene_Menu(const sf::Font &font, GameEngine *gameEngine) : m_menuText(sf::Text(font)), Scene(gameEngine)
{
    init();
}

Scene_Menu::Scene_Menu(const Scene_Menu &obj) : m_menuText(obj.m_menuText), m_menuStrings(obj.m_menuStrings), m_title(obj.m_title), m_levelPaths(obj.m_levelPaths), m_selectedMenuIndex(obj.m_selectedMenuIndex)
{
}

void Scene_Menu::init()
{
    // registerAction(sf::Keyboard::Scancode::W, SceneMenuActions::UP);
    // registerAction(sf::Keyboard::Scancode::S, SceneMenuActions::DOWN);
    // registerAction(sf::Keyboard::Scancode::D, SceneMenuActions::PLAY);
    // registerAction(sf::Keyboard::Scancode::Escape, SceneMenuActions::QUIT);
    registerAction(sf::Keyboard::Scancode::W, SceneMenuActions::UP);
    registerAction(sf::Keyboard::Scancode::S, SceneMenuActions::DOWN);
    registerAction(sf::Keyboard::Scancode::D, SceneMenuActions::PLAY);
    registerAction(sf::Keyboard::Scancode::Escape, SceneMenuActions::QUIT);
    registerAction(sf::Keyboard::Scancode::G, SceneMenuActions::TOGGLE_GRID);

    m_title = "Mega Mario";
    m_menuStrings.push_back("Level 1");
    m_menuStrings.push_back("Level 2");
    m_menuStrings.push_back("Level 3");

    m_levelPaths.push_back("../config/level1config.txt");
    m_levelPaths.push_back("../config/level1config.txt");
    m_levelPaths.push_back("../config/level1config.txt");

    m_menuText.setFont(m_game->getAssets().getFont("byteSized2"));
    m_menuText.setCharacterSize(64);

    auto brick = m_entityManager.addEntity(EntityType::TILE); // auto brick = m_entityManager.addEntity("tile");
    // IMPORTANT: always add the CAnimation compnent first so that gridToMidPixel can compute correctly
    // brick->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    brick->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::QUESTION), true); // brick->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    brick->addComponent<CTransform>(Vec2(1280 / 2 - 30, 768 / 2));

    auto brick2 = m_entityManager.addEntity(EntityType::TILE); // auto brick2 = m_entityManager.addEntity("tile");
    // IMPORTANT: always add the CAnimation compnent first so that gridToMidPixel can compute correctly
    // brick->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    brick2->addComponent<CAnimation>(m_game->getAssets().getAnimation("Stand"), true);
    brick2->addComponent<CTransform>(Vec2(1280 / 2, 768 / 2));

    auto brick3 = m_entityManager.addEntity(EntityType::TILE); // auto brick3 = m_entityManager.addEntity("tile");
    // IMPORTANT: always add the CAnimation compnent first so that gridToMidPixel can compute correctly
    // brick->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    brick3->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    brick3->addComponent<CTransform>(Vec2(1280 / 2 + 30, 768 / 2));

    auto block = m_entityManager.addEntity(EntityType::TILE); // auto block = m_entityManager.addEntity("tile");
    block->addComponent<CAnimation>(m_game->getAssets().getAnimation("Block"), true);
    block->addComponent<CTransform>(Vec2((9 * 64) + 32, (9 * 64) - 32));
    const int gridBlockSize = 64;
    const Vec2 textSize = block->getComponent<CAnimation>().animation.getSize();
    const Vec2 textToGridBlockRatio = {64 / block->getComponent<CAnimation>().animation.getSize().x, 64 / block->getComponent<CAnimation>().animation.getSize().y};
    block->getComponent<CTransform>().scale = textToGridBlockRatio;

    auto jumpManBlock = m_entityManager.addEntity(EntityType::TILE);
    jumpManBlock->addComponent<CAnimation>(m_game->getAssets().getAnimation(AnimationType::JUMP), true);
    jumpManBlock->addComponent<CTransform>(Vec2(1280 / 2 + 90, 768 / 2 - 64));

    // drawLine({350, 350},{650, 650});
}

void Scene_Menu::update()
{
    m_entityManager.update();
    sRender();
}

void Scene_Menu::onEnd()
{
    // m_game->window().clear(sf::Color::White);
    m_game->window().close();
    // TODO: Figure out what to do on end here
}

void Scene_Menu::sDoAction(const Action &action)
{
    if (action.type() == ActionType::START)
    {

        if (action.name() == SceneMenuActions::UP)
        {
            if (m_selectedMenuIndex == 0)
            {
                m_selectedMenuIndex = m_menuStrings.size() - 1;
            }
            else
            {
                m_selectedMenuIndex--;
            }
        }
        else if (action.name() == SceneMenuActions::DOWN)
        {
            if (m_selectedMenuIndex >= m_menuStrings.size() - 1)
            {
                m_selectedMenuIndex = 0;
            }
            else
            {
                m_selectedMenuIndex++;
            }
        }
        else if (action.name() == SceneMenuActions::PLAY)
        {
            // m_game->changeScene(SceneMenuActions::PLAY, std::make_shared<Scene_Play>(m_game, m_selectedMenuIndex, m_game->getAssets().getFont("FontName")), true); // This is butchured fasho
            m_game->changeScene(SceneMenuActions::PLAY, std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex], m_game->getAssets().getFont("byteSized2")), true);
            // m_game->changeScene(SceneMenuActions::PLAY, std::make_shared<Scene_Play>(m_game, "Level 1", m_game->getAssets().getFont("byteSized2")), false);
        }
        else if (action.name() == SceneMenuActions::QUIT)
        {
            onEnd();
        }
        else if (action.name() == SceneMenuActions::TOGGLE_GRID)
        {
            m_drawGrid = !m_drawGrid;
        }
    }
    else if (action.type() == ActionType::END)
    {
    }
}

void Scene_Menu::sRender()
{
    // clear the wdnow to a blue
    m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().clear(sf::Color(100, 100, 255));

    // draw the game title in the top-left of the screen
    m_menuText.setCharacterSize(48);
    m_menuText.setString(m_title);
    m_menuText.setFillColor(sf::Color::Black);
    m_menuText.setPosition(sf::Vector2f(10, 10));
    m_game->window().draw(m_menuText);

    // draw all of the menu options
    for (size_t i = 0; i < m_menuStrings.size(); i++)
    {
        m_menuText.setString(m_menuStrings[i]);
        m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::Cyan : sf::Color::White);
        m_menuText.setPosition(sf::Vector2f(10, 110 + i * 72));
        m_game->window().draw(m_menuText);
    }

    // draw the controls in the bottom-left
    sf::Text controlsText(m_game->getAssets().getFont("byteSized2"), "up: w   down: s  play: d  back: esc");
    controlsText.setCharacterSize(20);
    controlsText.setFillColor(sf::Color::Black);
    controlsText.setPosition({0, static_cast<float>(m_game->window().getSize().y)});
    m_game->window().draw(controlsText);

    for (auto e : m_entityManager.getEntities())
    {
        auto &transform = e->getComponent<CTransform>();

        if (e->hasComponent<CAnimation>())
        {
            auto &animation = e->getComponent<CAnimation>().animation;
            animation.update(); // ??? OG class concempt didn't have any animations in menu scene
            auto tempVari = animation.getSprite();
            auto tempVari2 = animation.getSize();
            animation.getSprite().setRotation(sf::degrees(transform.angle));
            animation.getSprite().setPosition({transform.pos.x, transform.pos.y}); // Check if Transform exists?
            animation.getSprite().setScale({transform.scale.x, transform.scale.y});
            const sf::Vector2f tempVari3 = animation.getSprite().getScale();
            const sf::FloatRect tempVari4 = animation.getSprite().getGlobalBounds();
            m_game->window().draw(animation.getSprite());
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
        debugText.setFillColor(sf::Color::Black);
        debugText.setPosition({static_cast<float>(m_game->window().getSize().x / 2), 32});
        m_game->window().draw(debugText);
    }

    m_game->window().display();
}

void Scene_Menu::drawLine(const Vec2 &p1, const Vec2 &p2) const
{
    sf::Vertex line[] = {{sf::Vector2f(p1.x, p1.y)}, {sf::Vector2f(p2.x, p2.y)}};
    m_game->window().draw(line, 2, sf::PrimitiveType::Lines);
}

void Scene_Menu::drawGrid() const
{
    const sf::Vector2u window_size = m_game->window().getSize();
    const int gridBlockSize = 64;
    const int maxGridLines = window_size.x > window_size.y ? window_size.x / gridBlockSize : window_size.y / gridBlockSize;
    const int numVerticleLinePoints = window_size.x / gridBlockSize;

    for (float i = 1; i < maxGridLines; i++)
    {
        drawLine({i * gridBlockSize, 0}, {i * 64, static_cast<float>(window_size.y)});
        drawLine({0, i * gridBlockSize}, {static_cast<float>(window_size.x), i * gridBlockSize});

        for (float j = 0; j < numVerticleLinePoints; j++)
        {
            std::ostringstream coordinateString;
            coordinateString << "( " << i << ", " << j << ")";

            const sf::Font coordStringFont = m_menuText.getFont();
            sf::Text coordinateText(coordStringFont, coordinateString.str(), 10);

            coordinateText.setPosition({i * gridBlockSize, j * gridBlockSize});
            m_game->window().draw(coordinateText);
        }
    }
}

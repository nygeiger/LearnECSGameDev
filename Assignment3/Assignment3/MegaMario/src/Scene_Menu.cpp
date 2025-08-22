#include "../headers/Scene_Menu.h"
#include "../headers/Scene_Play.h"
#include "../headers/Assets.h"
#include "../headers/GameEngine.h"
#include "../headers/Components.h"
#include "../headers/Action.h"

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
    registerAction(sf::Keyboard::Scancode::W, "UP");
    registerAction(sf::Keyboard::Scancode::S, "DOWN");
    registerAction(sf::Keyboard::Scancode::D, "PLAY");
    registerAction(sf::Keyboard::Scancode::Escape, "QUIT");

    m_title = "Mega Mario";
    m_menuStrings.push_back("Level 1");
    m_menuStrings.push_back("Level 2");
    m_menuStrings.push_back("Level 3");

    m_levelPaths.push_back("level1.txt");
    m_levelPaths.push_back("level2.txt");
    m_levelPaths.push_back("level3.txt");

    m_menuText.setFont(m_game->getAssets().getFont("byteSized2"));
    m_menuText.setCharacterSize(64);
}

void Scene_Menu::update()
{
    m_entityManager.update();
    sRender();
}

void Scene_Menu::onEnd()
{
    // TODO: Figure out what to do on end here
}

void Scene_Menu::sDoAction(const Action &action)
{
    if (action.type() == ActionType::START)
    {

        if (action.name() == "UP")
        {
            // if (m_selectedMenuIndex > 0) {}
            // else {m_selectedMenuIndex = m_menuStrings.size() - /*fill the rest*/}
        }
        else if (action.name() == "DOWN")
        {
            // m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_
        }
        else if (action.name() == "PLAY")
        {
            // m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, m_selectedMenuIndex, m_game->getAssets().getFont("FontName")), true); // This is butchured fasho
            m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, "Level 1", m_game->getAssets().getFont("byteSized2")), true); // This is butchured fasho
        }
        else if (action.name() == "QUIT")
        {
            onEnd();
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
        // m_menuText.setString(m_menuStrings[i]);
        // m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::Cyan : sf::Color::White);
        // m_menuText.setPosition(sf::Vector2f(10, 110 + i * 72));
        // m_game->window().draw(m_menuText);

        m_menuText.setString(m_menuStrings[i]);
        m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::Cyan : sf::Color::White);
        m_menuText.setPosition(sf::Vector2f(10, 110 + i * 72));
        m_game->window().draw(m_menuText);
    }

    // draw the controls in the bottom-left
    sf::Text controlsText(m_game->getAssets().getFont("byteSized2"), "up: w   down: s  play: d  back: ");
    controlsText.setCharacterSize(20);
    controlsText.setFillColor(sf::Color::Black);
    // controlsText.setPosition({});
    m_game->window().draw(controlsText);
    // m_menuText.setCharacterSize(20);
    // m_menuText.setFillColor(sf::Color::Black);
    // m_menuText.setString("up: w   down: s  play: d  back: ");
    m_game->window().display();
}
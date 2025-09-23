#include "headers/Scene.h"

Scene::Scene() : m_game(nullptr) {}

Scene::Scene(GameEngine *gameEngine) : m_game(gameEngine) {}

void Scene::setPaused(bool paused)
{
    m_paused = paused;
}

Vec2 Scene::getTextureToSizeRatio(const Vec2 startingSize, Vec2 desiredSize) const
{
    const Vec2 textToGridBlockRatio = {desiredSize.x / startingSize.x, desiredSize.y / startingSize.y};
    return textToGridBlockRatio;
}

void Scene::simulate(const size_t frames)
{ // Probably related to the ai stuff
}

void Scene::registerAction(sf::Keyboard::Scancode inputKey, const std::string &actionName)
{
    m_actionMap[inputKey] = actionName;
}

size_t Scene::width() const
{
    // return m_game->m_window.getSize().x;
    return 0;
}

size_t Scene::height() const
{
    // return m_game->m_window.getSize().x;
    return 0;
}

bool Scene::hasEnded() const
{
    return m_hasEnded;
}

size_t Scene::currentFrame() const
{
    return m_currentFrame;
}

const ActionMap &Scene::getActionMap() const
{
    return m_actionMap;
}
#include "headers/Scene.h"

Scene::Scene() : m_game(nullptr) {}

Scene::Scene(GameEngine *gameEngine) : m_game(gameEngine) {}

void Scene::setPaused(bool paused)
{
    m_paused = paused;
}

/// @brief Returns the ratio of starting size {x,y} to desired size {x,y}
///         (ex. starting = {16, 64}, desired = {32, 32}, return = {2.00, 0.5})
/// @param startingSize current dimensions of the texture
/// @param desiredSize  desired texture dimensions
/// @return             the ration from starting to desired size so that startingSize * return = desiredSize
Vec2 Scene::getTextureToSizeRatio(const Vec2 startingSize, Vec2 desiredSize) const
{
    const Vec2 textToGridBlockRatio(desiredSize.x / startingSize.x, desiredSize.y / startingSize.y);
    return textToGridBlockRatio;
} // should this go in animation class?

void Scene::simulate(const size_t frames)
{ // Probably related to the ai stuff from the assignment demo
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
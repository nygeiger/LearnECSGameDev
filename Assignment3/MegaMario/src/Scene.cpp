#include "headers/Scene.h"

Scene::Scene() : m_game(nullptr) {}

Scene::Scene(GameEngine *gameEngine) : m_game(gameEngine) {}

void Scene::setPaused(bool paused) {
    m_paused = paused;
}

void Scene::simulate(const size_t frames) { // Probably related to the ai stuff

}

void Scene::registerAction(sf::Keyboard::Scancode inputKey, const std::string &actionName) {
    m_actionMap[inputKey] = actionName;
}

size_t Scene::width() const {
    // return m_game->m_window.getSize().x;
    return 0;
}

size_t Scene::height() const {
    // return m_game->m_window.getSize().x;
    return 0;
}

bool Scene::hasEnded() const {
    return m_hasEnded;
}

size_t Scene::currentFrame() const {
    return m_currentFrame;
}

const ActionMap& Scene::getActionMap() const {
    return m_actionMap;
}

// void Scene::drawLine(const Vec2& p1, const Vec2& p2) { // stlen from sceneplay
//     if (m_game != nullptr) {
//         sf::Vertex line[] = {{sf::Vector2f(p1.x, p1.y), sf::Color::White}, {sf::Vector2f(p2.x, p2.y), sf::Color::White}};
//         m_game->window().draw(line, 2, sf::PrimitiveType::Lines);
//     }
//     // sf::Vertex line[] = {{sf::Vector2f(p1.x, p1.y)}, {sf::Vector2f(p2.x, p2.y)}};
//     // m_game->window().draw(line, 2, sf::Lines);

//     // const Vec2 vecWithPointDiff = p2 - p1;
//     // // sf::RectangleShape line({5,5});
//     // sf::RectangleShape line({std::abs(vecWithPointDiff.x), std::abs(vecWithPointDiff.y)});
    
//     // line.setPosition({p1.x, p1.y});
// }


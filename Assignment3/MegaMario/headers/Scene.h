#ifndef SCENE_H
#define SCENE_H

#include "Action.h"
#include "EntityManager.h"

#include <memory>

class GameEngine;

typedef std::map<sf::Keyboard::Scancode, std::string> ActionMap;

class Scene
{
protected:
    GameEngine *m_game = nullptr;
    EntityManager m_entityManager;
    ActionMap m_actionMap;
    bool m_paused = false;
    bool m_hasEnded = false;
    size_t m_currentFrame = 0;

    virtual void onEnd() = 0;
    void setPaused(bool paused);
    Vec2 getTextureToSizeRatio(const Vec2 startingSize, Vec2 desiredSize) const;

public:
    Scene();
    Scene(GameEngine *gameEngine);

    virtual void update() = 0;
    virtual void sDoInput(const Action &action) = 0;
    void registerAction(sf::Keyboard::Scancode inputKey, const std::string &actionName);
    virtual void sRender() = 0;

    void simulate(const size_t frames);

    size_t width() const;
    size_t height() const;
    size_t currentFrame() const;

    bool hasEnded() const;
    const ActionMap &getActionMap() const;
    virtual void drawLine(const Vec2 &p1, const Vec2 &p2) const = 0;
};

#endif
/* virtual:
    Virtual functions are member functions whose behavior can be overridden in derived classes.

    As opposed to non-virtual functions, the overriding behavior is preserved even if there is no
    compile-time information about the actual type of the class (Pointers and Refrences).

   <In Detail> 
  If some member function vf is declared as virtual in a class Base, and some class Derived, which is derived,
  directly or indirectly, from Base, has a declaration for member function with the same
  - name
  - parameter type list (but not the return type)
  - cv-qualifiers
  - ref-qualifiers

Then this function in the class Derived is also virtual (whether or not the keyword virtual is used in its declaration)
and overrides Base::vf (whether or not the specifier override is used in its declaration).

Base::vf does not need to be accessible or visible to be overridden. (Base::vf can be declared private, or Base can be
inherited using private inheritance. Any members with the same name in a base class of Derived which inherits Base do not
matter for override determination, even if they would hide Base::vf during name lookup.)

https://en.cppreference.com/w/cpp/language/virtual.html
*/
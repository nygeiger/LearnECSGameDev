#ifndef ENTITY_H
#define ENTITY_H

#include <tuple>
#include <string>

#include "Components.h"

class EntityManager;

typedef std::tuple<CTransform, CLifespan, CInput, CBoundingBox, CGravity, CState, CAnimation, CActionFrameRecord> ComponentTuple;

class Entity
{
    friend class EntityManager;

private:
    // entity properties
    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "default";
    ComponentTuple m_components; // adding/removing comps is easier with 1 collection (Tuple) vs Pointers

    // constructor and destructor

    Entity(const size_t id, const std::string &tag);

public:
    //  ***** DEPRECATED ******
    // component pointers
    // std::shared_ptr<CTransform> cTransform;
    // std::shared_ptr<CShape> cShape;
    // std::shared_ptr<CCollision> cCollision;
    // std::shared_ptr<CInput> cInput;
    // std::shared_ptr<CScore> cScore;
    // std::shared_ptr<CLifespan> cLifespan;
    //  ***** END_DEPRECATED ******

    // privat member access functions
    bool isActive() const;
    const std::string &tag() const;
    const size_t id() const;
    void destroy();

    template <typename T>
    bool hasComponent()
    {
        return getComponent<T>().has;
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs &&...mArgs)
    {
        auto& component = getComponent<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
        return component;
    }

    template <typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};

namespace EntityType
{
    static const std::string PLAYER = "player";
    static const std::string ENEMY = "enemy";
    static const std::string TILE = "tile";
    static const std::string DECORATION = "decoration";
    static const std::string BULLET = "bullet";
    static const std::string SPECIAL_WEAPON = "special_weapon";
    static const std::string SMALL_ENEMY = "small_enemy";
    static const std::string COLLISION_VISUAL = "collision_visual";
};

#endif
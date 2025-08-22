#ifndef ENTITY_H
#define ENTITY_H

#include <tuple>
#include <string>

#include "Components.h"

class EntityManager;

typedef std::tuple<CTransform, CLifespan, CInput, CBoundingBox, CGravity, CState, CAnimation> ComponentTuple;
// using ComponentTuple =  std::tuple<std::string, CTransform, CLifespan, CInput, CBoundingBox, /*CAnimation,*/ CGravity, CState>;
// std::get<CTransform>(ComponentTuple); <- to get the CTransform stored in this Tuple

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

    // template <typename T>
    // bool hasComponent() const
    // {
    //     return getComponent<const T>().has;
    // }
    template <typename T>
    bool hasComponent()
    {
        return getComponent<T>().has;
    }


    // template <typename T, typename... TArgs>
    // T& addComponent(TArgs&&... mArgs) {
    //     auto& component = getComponent<T>();
    //     // component = T(std::forwared<TArgs>(mArgs)...);
    //     component = T(std::forward<TArgs>(mArgs)...);
    //     component.has = true;
    //     return component;
    // }
    template <typename T, typename... TArgs>
    T& addComponent(TArgs &&...mArgs)
    {
        auto& component = getComponent<T>();
        // component = T(std::forwared<TArgs>(mArgs)...);
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
        return component;
    }

    // template<typename T>
    // T& getComponent() const{
    //     return std::get<const T>(m_components);
    // }
    // template <typename T>
    // const T& getComponent() const
    // {
    //     return std::as_const(std::get<T>(m_components));
    // }
    // template<typename T>
    // T& getComponent() const{
    //     return std::get<const T>(m_components);
    // }
    template <typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    // template<typename T>
    // void removeComponent() {
    //     getComponent<const T>() = T();
    // }
    template <typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};

#endif
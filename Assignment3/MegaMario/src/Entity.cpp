#include "../headers/Entity.h"

Entity::Entity(const size_t id, const std::string & tag) : m_id(id), m_tag(tag){
    // // m_components = std::make_tuple(CTransform, CLifespan, CInput, CBoundingBox, CAnimation, CGravity, CState);
    // m_components = std::make_tuple(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    // ComponentTuple tempVari = new ComponentTuple;
};

bool Entity::isActive() const {
    return m_active;
}

const std::string & Entity::tag() const {
    return m_tag;
}

const size_t Entity::id() const {
    return m_id;
}

void Entity::destroy() {
    m_active = false;
}

#include "../headers/Entity.h"

Entity::Entity(const size_t id, const std::string & tag) : m_id(id), m_tag(tag) {};

bool Entity::isActive() const {
    // TODO
    return m_active;
}

const std::string & Entity::tag() const {
    // TODO
    return m_tag;
}

const size_t Entity::id() const {
    // TODO
    return m_id;
}

void Entity::destroy() {
    m_active = false;
}

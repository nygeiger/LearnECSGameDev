#include "../headers/Action.h"

Action::Action() = default;

Action::Action(const std::string &name, const std::string &type): m_name(name), m_type(type){};

const std::string &Action::name() const
{
    return m_name;
}

const std::string& Action::type() const
{
    return m_type;
}

std::string Action::toString() const
{
    return std::string(m_name + " " + m_type);
}
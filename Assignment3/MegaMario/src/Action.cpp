#include "headers/Action.h"

Action::Action(const std::string &name, const ActionType& type): m_name(name), m_type(type){};

const std::string &Action::name() const
{
    return m_name;
}

const ActionType& Action::type() const
{
    return m_type;
}

const std::string Action::getTypeString() const {
    switch (m_type)
    {
    case ActionType::START:
        return "START";
     case ActionType::END:
        return "END";
     case ActionType::NONE:
        return "NONE";    
    default:
        break;
    }
}

// std::string Action::toString() const
// {
//     return std::string(m_name + " " + m_type);
// }
std::string Action::toString() const
{
    return std::string(m_name + " " + getTypeString());
}
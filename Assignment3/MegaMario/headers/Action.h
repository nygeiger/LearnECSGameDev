#ifndef ACTION_H_
#define ACTION_H_

#include <string>

enum ActionType {START, END, NONE};
class Action {
    std::string m_name = "NONE";
    ActionType m_type = ActionType::NONE;

    public:
        Action() = default;
        Action(const std::string &name, const ActionType& type);
        const std::string& name() const;
        const ActionType& type() const;
        const std::string getTypeString() const;
        std::string toString() const;
};

#endif
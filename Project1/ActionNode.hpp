#include "NodeState.hpp"

class ActionNode : public BTNode {
private:
    string actionName;
public:
    ActionNode(string name) : actionName(name) {}
    NodeState execute() override;
};
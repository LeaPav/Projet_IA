#pragma once
#include "NodeState.hpp"

class ActionNode1 : public BTNode {
private:
    std::string actionName;
    Enemy& enem1;
public:
    ActionNode1(std::string name, Enemy& enemy);
    NodeState execute() override;
};



class ActionNode2 : public BTNode {
private:
    std::string actionName;
    Enemy& enem2;
public:
    ActionNode2(std::string name, Enemy& enemy);
    NodeState execute() override;
};
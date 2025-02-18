#pragma once
#include "ActionNode.hpp"
#include "ConditionNode.hpp"
class SelectorNode : public NodeS {
private:
    FunctionA actionA;
    FunctionB actionB;
    ConditionNode condition;

public:
    bool Execute() override;
};
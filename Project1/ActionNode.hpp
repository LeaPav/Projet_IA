#pragma once
#include "NodeState.hpp"

class FunctionA : public NodeS {
public:
    FunctionA() {};
    bool Execute() override;
};

// Action B
class FunctionB : public NodeS {
public:
    FunctionB(){}
    bool Execute() override;
};
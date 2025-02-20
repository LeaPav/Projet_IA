#pragma once
#include "NodeState.hpp"
class FunctionA : public NodeS {
public:
    bool Execute() override;
};

// Action B
class FunctionB : public NodeS {
public:
    bool Execute() override;
};
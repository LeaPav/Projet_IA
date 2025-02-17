#include "NodeState.hpp"
class FunctionA : public NodeS {
public:
    bool Execute() override;
};

// Action B (garde passive)
class FunctionB : public NodeS {
public:
    bool Execute() override;
};
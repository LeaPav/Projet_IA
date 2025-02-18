#pragma once
#include "NodeState.hpp"
class ConditionNode :public NodeS {
public:
    ConditionNode(){}
    bool Execute() override;
    void DistanceM();
private:
    bool VerifDistance;



};

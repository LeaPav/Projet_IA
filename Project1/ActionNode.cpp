#include "ActionNode.hpp"

NodeState ActionNode::execute(){
    std::cout << "Action: " << actionName << std::endl;
    return NodeState::SUCCESS;
}
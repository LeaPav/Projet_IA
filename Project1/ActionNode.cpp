#include "ActionNode.hpp"

NodeState ActionNode::execute(){
    cout << "Action: " << actionName << endl;
    return NodeState::SUCCESS;
}
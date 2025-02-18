#include"SelctorNode.hpp"
void SelectorNode::AddChild(unique_ptr<BTNode> child) {
    children.push_back(move(child));
}
NodeState SelectorNode::execute(){
    for (auto& child : children) {
        if (child->execute() == NodeState::SUCCESS) {
            return NodeState::SUCCESS;
        }
    }
    return NodeState::FAILURE;
}
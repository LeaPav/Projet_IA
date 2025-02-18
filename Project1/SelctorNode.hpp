#include "NodeState.hpp"

class SelectorNode : public BTNode {
private:
    vector<unique_ptr<BTNode>> children;
public:
    void AddChild(unique_ptr<BTNode> child);
    NodeState execute() override;
};
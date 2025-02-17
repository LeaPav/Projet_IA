#include"SelctorNode.hpp"
bool SelectorNode::Execute(){
    if (condition.Execute()) {
        return actionA.Execute();
    }
    else {
        return actionB.Execute();
    }
}
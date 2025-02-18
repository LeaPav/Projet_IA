#include"SelctorNode.hpp"

bool SelectorNode::Execute(){
    if (condition.Execute() == true) {
        return actionA.Execute();
    }
    else if (condition.Execute() == false) {
        return actionB.Execute();
    }
}
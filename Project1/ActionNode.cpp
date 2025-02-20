
#include "ActionNode.hpp"

    ActionNode1::ActionNode1(std::string name, Enemy& enemy) : actionName(name),enem1(enemy) {}
    NodeState ActionNode1::execute(){
        enem1.setCurrentState(enem1.PATROL);
        return NodeState::SUCCESS;
    }


    ActionNode2::ActionNode2(std::string name, Enemy& enemy) : actionName(name), enem2(enemy) {}
    NodeState ActionNode2::execute(){
        enem2.setCurrentState(enem2.PROTECT);
        return NodeState::SUCCESS;
    }


#pragma once

#include "SelctorNode.hpp"
#include "NodeState.hpp"
#include"Blackboard.hpp"
#include"ActionNode.hpp"
#include"SequenceNode.hpp"
#include "ConditionNode.hpp"
using namespace std;
using namespace sf;
class FSM {
public:
    FSM();
    void run(float deltaTime, Grid& grid, sf::Vector2i& playerPos,Enemy* enemy);
    void Behevior();
    void InitBehevior(Enemy& enemy,Player& player);
private:
    Blackboard blackboard;
    unique_ptr<SelectorNode> root ;
    unique_ptr<SequenceNode>sequenceProtect;
    unique_ptr<SequenceNode>sequencePatrol;
};


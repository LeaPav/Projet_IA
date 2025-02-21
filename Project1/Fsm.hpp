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
    FSM(Enemy& enemY);
    Enemy& _enemy;
    void run(float deltaTime, Grid& grid, sf::Vector2i& playerPos,Enemy& enemy, Vector2i& objetPos, Objet& objet);
    void InitBehevior(Enemy& enemy1,Player& player);

private:
    Blackboard blackboard;
    unique_ptr<SelectorNode> root ;
    unique_ptr<SequenceNode>sequenceProtect;
    unique_ptr<SequenceNode>sequencePatrol;
    Time timeC_fsm;
};


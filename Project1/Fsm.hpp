#pragma once

#include "SelctorNode.hpp"
#include "NodeState.hpp"
#include"Blackboard.hpp"
#include"ActionNode.hpp"
#include"SequenceNode.hpp"
#include "ConditionNode.hpp"

class FSM {
public:
    FSM();
    void run(float deltaTime, Grid& grid, sf::Vector2i& playerPos,Enemy* enemy);
    void Behevior();
    void InitBehevior(Enemy& enemy,Player& player);
private:
};


#pragma once

#include "SelctorNode.hpp"
#include "Enemy.hpp"

class FSM {
public:
    FSM(Enemy& enemyRef);
    void run(float deltaTime, Grid& grid, sf::Vector2i& playerPos);
    void Behevior();
    Enemy& enemy;
    SelectorNode BeheviorTree;
};


#pragma once
#include "NodeState.hpp"
#include "Blackboard.hpp"

class ConditionNode : public BTNode {
private:
    Blackboard& blackboard;
    sf::Vector2f key;
    sf::Vector2f expectedValue;
public:
    ConditionNode(Blackboard& bb, sf::Vector2f k, sf::Vector2f value);

    NodeState execute() override;
};
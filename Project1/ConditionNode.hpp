#pragma once
#include "NodeState.hpp"
#include "Blackboard.hpp"

class ConditionNode : public BTNode {
private:
    Blackboard& blackboard;
    Vector2f key;
    Vector2f expectedValue;
    float objCordx;
    float objCordy;

public:
    ConditionNode(Blackboard& bb, sf::Vector2f k, sf::Vector2f value);

    NodeState execute() override;
    void ObjCord(Objet& objet);
};
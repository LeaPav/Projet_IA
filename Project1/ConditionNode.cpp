#include"ConditionNode.hpp"


ConditionNode::ConditionNode(Blackboard& bb, sf::Vector2f k, sf::Vector2f value)
    : blackboard(bb), key(k), expectedValue(value) {
}

NodeState ConditionNode::execute(){

    sf::Vector2f posPlayer = blackboard.GetValue("player pos");
    sf::Vector2f posEnemy = expectedValue;
    float distPlayer = std::hypot(posPlayer.x - objet.shape.getPosition().x,
        posPlayer.y - objet.shape.getPosition().y);
    float distEnemy = std::hypot(posEnemy.x - objet.shape.getPosition().x,
        posEnemy.y - objet.shape.getPosition().y);

    return (distPlayer < distEnemy) ? NodeState::SUCCESS : NodeState::FAILURE;
}
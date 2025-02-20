#include"ConditionNode.hpp"


ConditionNode::ConditionNode(Blackboard& bb, sf::Vector2f k, sf::Vector2f value)
    : blackboard(bb), key(k), expectedValue(value) {
}
void ConditionNode::ObjCord(Objet& objet) {
    objCordy = objet.shape.getPosition().y;
    objCordx = objet.shape.getPosition().x;
}

NodeState ConditionNode::execute(){
    sf::Vector2f posPlayer = blackboard.GetValue("player pos");
    sf::Vector2f posEnemy = expectedValue;
    float distPlayer = hypot(posPlayer.x - objCordx,
        posPlayer.y - objCordy);
    float distEnemy = hypot(posEnemy.x - objCordx,
        posEnemy.y - objCordy);

    std::cout << "ok condition : " << distPlayer << "  " << distEnemy << endl;
    return (distPlayer > distEnemy) ? NodeState::SUCCESS : NodeState::FAILURE;

}
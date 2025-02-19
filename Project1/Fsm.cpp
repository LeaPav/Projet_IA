#include "FSM.hpp"


FSM::FSM(){};
void FSM::Behevior() {
    
}
void FSM::InitBehevior(Enemy& enemy, Player& player) {
    
    
    blackboard.SetValue("player pos", player.shape.getPosition());
    root = make_unique<SelectorNode>();
    sequenceProtect = make_unique<SequenceNode>();
    sequencePatrol = make_unique<SequenceNode>();


    sequenceProtect->AddChild(std::make_unique<ConditionNode>(blackboard, blackboard.GetValue("player pos"), enemy.shape.getPosition()));



    sequenceProtect->AddChild(std::make_unique<ActionNode1>("Protection de l'item", enemy));
    sequencePatrol->AddChild(std::make_unique<ActionNode2>("Patrouiller", enemy));
    //problème dans les arguments de ActionNode , on a besoin d'un pointeur d'enemy

    root->AddChild(std::move(sequenceProtect));
    root->AddChild(std::move(sequencePatrol));
    root->execute();
}
void FSM::run(float deltaTime, Grid& grid, sf::Vector2i& playerPos,Enemy* enemy) {
    enemy->detectPlayer(grid, playerPos);

    switch (enemy->getCurrentState()) {
    case Enemy::PATROL:
        enemy->getShape().setFillColor(sf::Color::Red);
        enemy->patrol(deltaTime, grid);
        break;

    case Enemy::CHASE:
        enemy->getShape().setFillColor(sf::Color::Magenta);
        enemy->chase(grid, playerPos, deltaTime);
        break;

   
    case Enemy::SEARCH:
        enemy->getShape().setFillColor(sf::Color::Green);
        enemy->search(deltaTime, grid);
        break;

    case Enemy::BEHEVIOR:
        Behevior();
        break;


    case Enemy::PROTECT:
        enemy->getShape().setFillColor(sf::Color::Blue);
        enemy->protect();
        break;

    default:
        break;
    }
}

#include "FSM.hpp"


FSM::FSM(Enemy& enemY): _enemy(enemY){};
void FSM::InitBehevior(Enemy& enemy1, Player& player) {
    
    
    blackboard.SetValue("player pos", player.shape.getPosition());
    root = make_unique<SelectorNode>();
    sequenceProtect = make_unique<SequenceNode>();
    sequencePatrol = make_unique<SequenceNode>();


    sequenceProtect->AddChild(std::make_unique<ConditionNode>(blackboard, blackboard.GetValue("player pos"), enemy1.shape.getPosition()));


    sequenceProtect->AddChild(std::make_unique<ActionNode1>("Protection de l'item", enemy1));
    sequencePatrol->AddChild(std::make_unique<ActionNode2>("Patrouiller", enemy1));
    //problème dans les arguments de ActionNode , on a besoin d'un pointeur d'enemy


    root->AddChild(std::move(sequenceProtect));
    root->AddChild(std::move(sequencePatrol));
    
}
void FSM::run(float deltaTime, Grid& grid, sf::Vector2i& playerPos,Enemy& enemy,Vector2i& objetPos,Objet& objet) {
    enemy.updateCastRay(grid,playerPos);
    enemy.detectPlayer(grid, playerPos);
    enemy.revenge(objet, enemy, grid, playerPos, deltaTime);
    switch (enemy.getCurrentState()) {
    case Enemy::PATROL:
        enemy.getShape().setFillColor(sf::Color::Red);
        enemy.patrol(deltaTime, grid,playerPos);
        break;

    case Enemy::CHASE:
        timeC_fsm = enemy.getClock().getElapsedTime();
        enemy.setTime(timeC_fsm);
        //les deux ligne au dessus corresponde à ça : enemy.time = enemy.getClock().getElapsedTime();
        enemy.getShape().setFillColor(sf::Color::Magenta);
        enemy.chase(grid, playerPos, deltaTime);
        break;

   
    case Enemy::SEARCH:
        enemy.getShape().setFillColor(sf::Color::Green);
        enemy.search(deltaTime, grid, playerPos);

        break;

    case Enemy::BEHEVIOR:
        root->execute();
        break;


    case Enemy::PROTECT:
        enemy.getShape().setFillColor(sf::Color::Blue);
        enemy.protect(deltaTime, grid, objetPos/*, objet,enemy, playerPos*/);
        break;

    default:
        break;
    }
}

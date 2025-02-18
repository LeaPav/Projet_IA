#include "FSM.hpp"


FSM::FSM(Enemy& enemyRef) : enemy(enemyRef) {};
void FSM::Behevior() {
    
}
void FSM::run(float deltaTime, Grid& grid, sf::Vector2i& playerPos) {
    enemy.detectPlayer(grid, playerPos); // Détection du joueur

    switch (enemy.getCurrentState()) {
    case Enemy::PATROL:
        enemy.getShape().setFillColor(sf::Color::Red);
        enemy.patrol(deltaTime, grid);
        break;

    case Enemy::CHASE:
        enemy.getShape().setFillColor(sf::Color::Magenta);
        enemy.chase(grid, playerPos, deltaTime);
        break;

    case Enemy::BEHEVIOR:
        Behevior();
        break;

    case Enemy::SEARCH:
        enemy.getShape().setFillColor(sf::Color::Green);
        enemy.search(deltaTime, grid);
        break;

    case Enemy::PROTECT:
        enemy.getShape().setFillColor(sf::Color::Blue);
        enemy.protect();
        break;

    default:
        break;
    }
}

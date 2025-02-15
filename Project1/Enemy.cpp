#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) {}
enum Enemy::State { PATROL, CHASE, SEARCH,PROTECT };
void Enemy::setPath(std::vector<sf::Vector2i> newPath)
{
	if (!newPath.empty()) {
		path = newPath;
		currentIndexPath;
	}
}

void Enemy::update(float deltaTime, Grid& grid) {
    if (currentIndexPath >= path.size())
        return;

    switch (currentState) {
    case PATROL:
        //fonction de patrouille
         //if (/*fonction de d�tection du player*/) currentState = CHASE;
         //break;

    case CHASE:
        //fonction de chase avec le pathfinding
         //if (!/*fonction de d�tection du player*/) {
         //    currentState = SEARCH;
         //}
        break;

    case SEARCH:
        break;
    
    case PROTECT: 
        break;
    
    default: 
        break;
    }
}
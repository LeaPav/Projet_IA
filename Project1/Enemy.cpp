#include "Enemy.hpp"


Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) {}
void Enemy::setPath(std::vector<sf::Vector2i> newPath)
{
	if (!newPath.empty()) {
		path = newPath;
		currentIndexPath;
	}
}


void Enemy::patrol(sf::RectangleShape& forme, Grid& grid) {
    static int currentWaypoint = 0;
    static sf::Vector2f waypoints[4] = { sf::Vector2f(100,300), sf::Vector2f( 500,100), sf::Vector2f(100,  300), sf::Vector2f( 500, 300) };
    sf::Vector2f target = waypoints[currentWaypoint / CELL_SIZE];
    position = forme.getPosition();
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

   if(needsRepath == false){
       if (distance < 5.0f) {
           currentWaypoint = (currentWaypoint + 1) % 4;
       }
       else {
           direction /= distance;
           position += direction * 0.9f;
       }
   }
    sf::Vector2f newPositionE = position;
    sf::FloatRect newBoundsE(newPositionE, forme.getSize());

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    if (isWalkable(newBoundsE.left, newBoundsE.top) &&
        isWalkable(newBoundsE.left + newBoundsE.width - 1, newBoundsE.top) &&
        isWalkable(newBoundsE.left, newBoundsE.top + newBoundsE.height - 1) &&
        isWalkable(newBoundsE.left + newBoundsE.width - 1, newBoundsE.top + newBoundsE.height - 1)) {
        forme.setPosition(position);
    }
  
 /*   else{
        needsRepath = true;
    }
    if (needsRepath || path.empty()) {
        path = Pathfinding::findPath(grid,
            sf::Vector2i(static_cast<int>(newPositionE.x), static_cast<int>(newPositionE.y)),
            sf::Vector2i(static_cast<int>(target.x), static_cast<int>(target.y)));
        pathIndex = 0;
        needsRepath = false;
    }
    if (!path.empty() && pathIndex < path.size()) {
        Vector2i test(position) = path[pathIndex];
        if (pathIndex != path.size() - 1)
            pathIndex++;
    }*/
}

void Enemy::chase(sf::Vector2f playerPos, RectangleShape& form) {
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.2f;
    }

    shape.setPosition(position);
}



void Enemy::search(){


}
void Enemy::protect(){


}
























void Enemy::update(float deltaTime, Grid& grid,RectangleShape& forme) {
   
   /* if (currentIndexPath >= path.size())
        return;*/
    switch (currentState) {
    case PATROL:
        patrol(forme,grid);
        //if (/*fonction de détection du player*/) currentState = CHASE;
  /*  }*/
    //case CHASE:
    //    //fonction de chase avec le pathfinding
    //     //if (!/*fonction de détection du player*/) {
    //     //    currentState = SEARCH;
    //     //}
    //    break;

    //case SEARCH:
    //    search();
    //    break;
    //
    //case PROTECT: 
    //    protect();
    //    break;
    //
    //default: 
    //    break;
    }
}
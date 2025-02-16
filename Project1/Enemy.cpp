#include "Enemy.hpp"


Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) {}
void Enemy::setPath(std::vector<sf::Vector2i> newPath)
{
	if (!newPath.empty()) {
		path = newPath;
		currentIndexPath = 0;
	}
}


void Enemy::patrol(sf::RectangleShape& forme, Grid& grid) {
    static int currentWaypoint = 0;
    needsRepath == false;
    static Vector2f waypoints[4] = { Vector2f(100,300), Vector2f(500,100), Vector2f(100,  300), Vector2f(500, 300) };
    Vector2f target = waypoints[currentWaypoint];
    position = forme.getPosition();
    Vector2f direction = target - position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (needsRepath == false) {
        if (distance < 5.0f) {
            currentWaypoint = (currentWaypoint + 1) % 4;
        }
        else {
            direction /= distance;
            position += direction * 0.9f;
        }
    }
    Vector2f newPositionE = position;
    FloatRect newBoundsE(newPositionE, forme.getSize());

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
    else {
        needsRepath = true;
    }
    if (needsRepath) {
        auto newPath = Pathfinding::findPath(grid,
            Vector2i(static_cast<int>(newPositionE.x / CELL_SIZE), static_cast<int>(newPositionE.y / CELL_SIZE)),
            Vector2i(static_cast<int>(target.x / CELL_SIZE), static_cast<int>(target.y / CELL_SIZE)));

        if (!newPath.empty()) {
            path = newPath;
            pathIndex = 0;
            needsRepath = false;
        }
    }

    if (pathIndex < path.size()) {
        Vector2i nextStep = path[pathIndex];
        position = Vector2f(nextStep.x * CELL_SIZE, nextStep.y * CELL_SIZE);
        shape.setPosition(position);
        if (pathIndex < path.size() - 1)
            pathIndex++;
    }
    
}
void Enemy::chase(Vector2f playerPos, RectangleShape& form) {
    Vector2f direction = playerPos - position;
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
bool  Enemy::detectP(Vector2f playerPos, RectangleShape& form) {
    float radiusDetect = 50;
    detectionRadius = 50;
    float distance = std::sqrt(std::pow(playerPos.x - form.getPosition().x, 2) + std::pow(playerPos.y - form.getPosition().y, 2));
    return (distance < detectionRadius);
}























void Enemy::update(float deltaTime, Grid& grid,RectangleShape& forme) {
    patrol(forme, grid);
   /* if (currentIndexPath >= path.size())
        return;*/
    switch (currentState) {
    case PATROL:
        patrol(forme,grid);
        /*if (detectP()) {
            currentState = CHASE; 
            
        }*/
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
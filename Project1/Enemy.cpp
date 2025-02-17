#include "Enemy.hpp"



enum Enemy::State { PATROL, CHASE, SEARCH, PROTECT };
Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red), currentState(PATROL) {}

void Enemy::setPath(std::vector<sf::Vector2i> newPath)
{
    if (!newPath.empty()) {
        path = newPath;
        currentIndexPath = 0;
    }

}

void Enemy::setTarget(const sf::Vector2i& target)
{
    targetPosition = target;
}

void Enemy::detectPlayer(Grid& grid, const sf::Vector2i& playerPos)
{
    sf::Vector2i enemyPos = getGridPosition();

    int distance = std::abs(enemyPos.x - playerPos.x) + std::abs(enemyPos.y - playerPos.y);

    if (distance < 4 && currentState != CHASE) {
            currentState = CHASE;
            setTarget(playerPos);
            setPath(Pathfinding::findPath(grid, enemyPos, playerPos));

    }
    else if (distance > 10 && currentState == CHASE) {
        currentState = SEARCH;
        searchTargets = searchPoints(playerPos);
    }
}

void Enemy::update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) {

    detectPlayer(grid, playerPos);

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

        shape.setFillColor(sf::Color::Red);
        patrol(deltaTime, grid);
  
        break;
        //fonction de patrouille
         //if (/*fonction de détection du player*/) currentState = CHASE;
         //break;

    case CHASE:
        shape.setFillColor(sf::Color::Magenta);
        chase(grid, playerPos, deltaTime);
        //fonction de chase avec le pathfinding
         //if (!/*fonction de détection du player*/) {
         //    currentState = SEARCH;
         //}
        break;

    case SEARCH:
        shape.setFillColor(sf::Color::Green);
        search(deltaTime, grid);
        break;

    case PROTECT:
        break;

    default:
        break;
    }
}

void Enemy::moveAlongPath(float deltaTime, Grid& grid)
{
    if (currentIndexPath < path.size()) {

        sf::Vector2i nextCell = path[currentIndexPath];
        sf::Vector2f nextPosition = sf::Vector2f(nextCell.x * CELL_SIZE, nextCell.y * CELL_SIZE);

        sf::Vector2f direction = nextPosition - shape.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 0.1f) {
            direction /= distance;
            shape.setPosition(shape.getPosition() + direction * SPEED * deltaTime);
        } 
        if (distance < SPEED * deltaTime) {
            shape.setPosition(nextPosition);
            currentIndexPath++;
        }
    }
}

void Enemy::chase(Grid& grid, const sf::Vector2i& playerPos, float deltaTime)
{
   
    int dx = std::abs(playerPos.x - lastKnownPlayerPos.x);
    int dy = std::abs(playerPos.y - lastKnownPlayerPos.y);

    if (dx > 1 || dy > 1) {  
        lastKnownPlayerPos = playerPos;
        setPath(Pathfinding::findPath(grid, getGridPosition(), playerPos));  
    }

    moveAlongPath(deltaTime, grid);

}

void Enemy::patrol(float deltaTime, Grid& grid)
{
    static std::vector<sf::Vector2i> patrolPoints = { {2,2}, {8,2}, {8,8}, {12,13} };

    if (path.empty()) {
        targetPosition = patrolPoints[currentIndexPath];
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));  
        currentIndexPath = 0;
    }

    moveAlongPath(deltaTime, grid);
    
    sf::Vector2i enemyPos = getGridPosition();
    if (enemyPos == targetPosition) {
        currentIndexPath = (currentIndexPath + 1) % patrolPoints.size();
        targetPosition = patrolPoints[currentIndexPath];
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));  
    }
}

std::vector<sf::Vector2i> Enemy::searchPoints(sf::Vector2i lastKnownPos)
{
    std::vector<sf::Vector2i> points;
    points.push_back(lastKnownPos);
    points.push_back({ lastKnownPos.x + 2, lastKnownPos.y });
    points.push_back({ lastKnownPos.x - 2, lastKnownPos.y });
    points.push_back({ lastKnownPos.x, lastKnownPos.y + 2 });
    points.push_back({ lastKnownPos.x, lastKnownPos.y - 2 });
    return points;
}

void Enemy::search(float deltaTime, Grid& grid)
{
    if (searchTargets.empty()) {
        currentState = PATROL;
        currentIndexPath = 0;
        path.clear();
        return;
    }
    if (currentIndexPath >= path.size()) {
        searchTargets.erase(searchTargets.begin());
        if (!searchTargets.empty()) {
            std::vector<sf::Vector2i> newPath = Pathfinding::findPath(grid, getGridPosition(), searchTargets.front());

            if (!newPath.empty()) {
                setPath(newPath);
            }
            else {
                searchTargets.clear();
                return;
  
            }
        }
    }

    moveAlongPath(deltaTime, grid);
}

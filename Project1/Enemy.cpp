#include "Enemy.hpp"
#include <cmath>

using namespace sf;
using namespace std;

Enemy::Enemy(float x, float y) : Entity(x, y, Color::Red), currentState(PATROL) {}

void Enemy::setPath(vector<Vector2i> newPath)
{
    if (!newPath.empty()) {
        path = newPath;
        currentIndexPath = 0;
    }

}

void Enemy::setTarget(const Vector2i& target)
{
    targetPosition = target;
}

void Enemy::detectPlayer(Grid& grid, const Vector2i& playerPos)
{
   //Vector2i enemyPos = getGridPosition();

   // int distance = abs(enemyPos.x - playerPos.x) + abs(enemyPos.y - playerPos.y);

    Vector2f enemyPos = shape.getPosition();
    Vector2f playerWorldPos = Vector2f(playerPos.x * CELL_SIZE, playerPos.y * CELL_SIZE);

    float distance = sqrt(pow(playerWorldPos.x - enemyPos.x, 2) + pow(playerWorldPos.y - enemyPos.y, 2));

    if (distance > fovDistance * CELL_SIZE) {
        if (currentState == CHASE) {
            currentState = SEARCH;
            searchTargets = searchPoints(lastKnownPlayerPos);
        }
        return;
    }

    Vector2f enemyDirection = getDirection();

    Vector2f directionToPlayer = playerWorldPos - enemyPos;
    float norm = sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
    if (norm > 0) directionToPlayer /= norm;

    float dotProduct = enemyDirection.x * directionToPlayer.x + enemyDirection.y * directionToPlayer.y;
    float angleToPlayer = acos(dotProduct) * 180.0 / 3.14159f;

    bool playerVisible = (angleToPlayer < fovAngle * 0.5f) && lineOfSight(grid, playerPos);

    if (playerVisible && currentState !=CHASE) {
        currentState = CHASE;
        lastKnownPlayerPos = playerPos;

        setTarget(playerPos);
        setPath(Pathfinding::findPath(grid, getGridPosition(), playerPos));
    }
    else if (currentState == CHASE && !playerVisible) {
        currentState = SEARCH;
        searchTargets = searchPoints(lastKnownPlayerPos);
    }
    /*if (distance < 4 && currentState != CHASE && lineOfSight(grid, playerPos)) {
            currentState = CHASE;
            setTarget(playerPos);
            setPath(Pathfinding::findPath(grid, enemyPos, playerPos));

    }
    else if (distance > 10 && currentState == CHASE) {
        currentState = SEARCH;
        searchTargets = searchPoints(playerPos);
    }*/
}

void Enemy::update(float deltaTime, Grid& grid, Vector2i& playerPos) {

    detectPlayer(grid, playerPos);

    switch (currentState) {
    case PATROL:
        shape.setFillColor(Color::Red);
        patrol(deltaTime, grid, playerPos);
  
        break;
        //fonction de patrouille
         //if (/*fonction de détection du player*/) currentState = CHASE;
         //break;

    case CHASE:
        shape.setFillColor(Color::Magenta);
        chase(grid, playerPos, deltaTime);
        //fonction de chase avec le pathfinding
         //if (!/*fonction de détection du player*/) {
         //    currentState = SEARCH;
         //}
        break;

    case SEARCH:
        shape.setFillColor(Color::Green);
        search(deltaTime, grid, playerPos);
        break;

    case PROTECT:
        break;

    default:
        break;
    }
}

void Enemy::drawFov(RenderWindow& window, Grid& grid)
{
    ConvexShape fovShape;
    fovShape.setPointCount(3);
    fovShape.setFillColor(Color(255, 255, 0, 100)); 

    Vector2f enemyPos = shape.getPosition() + Vector2f(CELL_SIZE / 2, CELL_SIZE / 2); 

    Vector2f direction = getDirection(); 

    float leftAngle = atan2(direction.y, direction.x) - (fovAngle * 0.5f * 3.14159f / 180.0f);
    float rightAngle = atan2(direction.y, direction.x) + (fovAngle * 0.5f * 3.14159f / 180.0f);

    Vector2f leftPoint = castRay(grid, enemyPos, leftAngle);
    Vector2f rightPoint = castRay(grid, enemyPos, rightAngle);

    fovShape.setPoint(0, enemyPos);
    fovShape.setPoint(1, leftPoint);
    fovShape.setPoint(2, rightPoint);

    window.draw(fovShape);
}

void Enemy::moveAlongPath(float deltaTime, Grid& grid, const Vector2i& playerPos)
{
    float stopDistance = CELL_SIZE * 1.5f;

    if (currentIndexPath < path.size()) {

        Vector2i nextCell = path[currentIndexPath];
        Vector2f nextPosition = Vector2f(nextCell.x * CELL_SIZE, nextCell.y * CELL_SIZE);

        Vector2f direction = nextPosition - shape.getPosition();
        Vector2f enemyPosition = shape.getPosition();

        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        Vector2f playerWorldPos = Vector2f(playerPos.x * CELL_SIZE, playerPos.y * CELL_SIZE);
        float distanceToPlayer = sqrt(
            (playerWorldPos.x - enemyPosition.x) * (playerWorldPos.x - enemyPosition.x) +
            (playerWorldPos.y - enemyPosition.y) * (playerWorldPos.y - enemyPosition.y)
        );
        if (distanceToPlayer <= stopDistance) {
            return;
        }

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

void Enemy::initPatrol(Grid& grid)
{
    patrolPoints.clear();

    int maxX = GRID_WIDTH;
    int maxY = GRID_HEIGHT;

    int attempts = 0;
    while (patrolPoints.size() < 4 && attempts < 20) {
        int x = rand() % maxX;
        int y = rand() % maxY;
        if (grid.getCell(x, y).walkable) {
            patrolPoints.push_back(Vector2i(x, y));
        }
        attempts++;
    }

    if (!patrolPoints.empty()) {
        currentIndexPath = 0;
        targetPosition = patrolPoints[0];
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));
    }
}

void Enemy::chase(Grid& grid, const Vector2i& playerPos, float deltaTime)
{
 
    int dx = abs(playerPos.x - lastKnownPlayerPos.x);
    int dy = abs(playerPos.y - lastKnownPlayerPos.y);

    if (dx > 1 || dy > 1) {  
        lastKnownPlayerPos = playerPos;
        setPath(Pathfinding::findPath(grid, getGridPosition(), playerPos));  
    }
    
    moveAlongPath(deltaTime, grid, playerPos);

}

void Enemy::patrol(float deltaTime, Grid& grid, const Vector2i& playerPos)
{
   // static vector<Vector2i> patrolPoints = { {2,2}, {8,2}, {8,8}, {12,13} };

    if (patrolPoints.empty()) {
        initPatrol(grid);
        return;
    }
    if (path.empty()) {
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));  
        
    }

    moveAlongPath(deltaTime, grid, playerPos);
    
    Vector2i enemyPos = getGridPosition();
    if (enemyPos == targetPosition) {
        currentIndexPath = (currentIndexPath + 1) % patrolPoints.size();
        targetPosition = patrolPoints[currentIndexPath];
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));  
    }
}

vector<Vector2i> Enemy::searchPoints(Vector2i lastKnownPos)
{
    vector<Vector2i> points;
    points.push_back(lastKnownPos);
    points.push_back({ lastKnownPos.x + 2, lastKnownPos.y });
    points.push_back({ lastKnownPos.x - 2, lastKnownPos.y });
    points.push_back({ lastKnownPos.x, lastKnownPos.y + 2 });
    points.push_back({ lastKnownPos.x, lastKnownPos.y - 2 });
    return points;
}

void Enemy::search(float deltaTime, Grid& grid, const Vector2i& playerPos)
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
            vector<Vector2i> newPath = Pathfinding::findPath(grid, getGridPosition(), searchTargets.front());

            if (!newPath.empty()) {
                setPath(newPath);
            }
            else {
                searchTargets.clear();
                return;
  
            }
        }
    }

    moveAlongPath(deltaTime, grid, playerPos);
}

bool Enemy::lineOfSight(Grid& grid, const Vector2i& playerPos)
{
    Vector2i enemyPos = getGridPosition();


    int dx = abs(playerPos.x - enemyPos.x);
    int dy = abs(playerPos.y - enemyPos.y);
    int sx = (enemyPos.x < playerPos.x) ? 1 : -1;
    int sy = (enemyPos.y < playerPos.y) ? 1 : -1;
    int err = dx - dy;

    while (enemyPos.x != playerPos.x || enemyPos.y != playerPos.y) {
        if (!grid.getCell(enemyPos.x, enemyPos.y).walkable) {
            return false;
        }

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; enemyPos.x += sx; }
        if (e2 < dx) { err += dx; enemyPos.y += sy; }
    }

    return true; 
}

Vector2f Enemy::getDirection()
{
    if (path.empty() || currentIndexPath >= path.size())
        return Vector2f(1.0f, 0.f);

    Vector2f currentPos = shape.getPosition();
    Vector2i nextCell = path[currentIndexPath];
    Vector2f nextPos = Vector2f(nextCell.x * CELL_SIZE, nextCell.y * CELL_SIZE);

    Vector2f direction = nextPos - currentPos;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0) direction /= length;
    return direction;
}

Vector2f Enemy::castRay(Grid& grid, Vector2f start, float angle)
{
    Vector2f direction(cos(angle), sin(angle));
    Vector2f end = start;

    for (int i = 0; i < fovDistance * CELL_SIZE; i += 1)
    {
        end.x += direction.x;
        end.y += direction.y;

        Vector2i gridPos(static_cast<int>(end.x / CELL_SIZE), static_cast<int>(end.y / CELL_SIZE));

        if (gridPos.x < 0 || gridPos.y < 0 || gridPos.x >= GRID_WIDTH || gridPos.y >= GRID_HEIGHT) {
            break;
        }

        if (!grid.getCell(gridPos.x, gridPos.y).walkable) {
            break;
        }
    }

    return end;
}

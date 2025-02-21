#include "Enemy.hpp"
#include <cmath>


Enemy::Enemy(float x, float y) : Entity(x, y, Color::Red), currentState(PATROL), circleCenter(400, 400) {

    segments.resize(numSegments, VertexArray(Lines, 2));
}

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

    if (playerInSight && currentState != CHASE) {
        currentState = CHASE;
        lastKnownPlayerPos = playerPos;

        setTarget(playerPos);
        setPath(Pathfinding::findPath(grid, getGridPosition(), playerPos));

    }

    else if (currentState == CHASE && !playerInSight) {
        if (time.asSeconds() > 3) {
            currentState = SEARCH;
            searchTargets = searchPoints(lastKnownPlayerPos);

        }
    }
}

void Enemy::update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) {

}

void Enemy::updateCastRay(Grid& grid, const Vector2i& playerPos)
{

    circleCenter = shape.getPosition() + Vector2f(CELL_SIZE / 2, CELL_SIZE / 2);

    float moveSpeed = 0.05f;
    Vector2f direction = getDirection();
    float directionAngle = atan2(direction.y, direction.x);

    playerInSight = false;
    for (int i = 0; i < numSegments; ++i)
    {

        float angle = directionAngle + (-angleRange / 2 + (angleRange * i / (numSegments - 1)));
        Vector2f endPoint(circleCenter.x + segmentLength * cos(angle), circleCenter.y + segmentLength * sin(angle));

        segments[i][0].position = circleCenter;
        segments[i][1].position = endPoint;

        Vector2f intersection;
        bool hitWall = false;
        bool hitPlayer = false;

        Vector2f currentPos = circleCenter;
        Vector2f rayDir = Vector2f(cos(angle), sin(angle));

        for (float j = 0; j < segmentLength; j += 1.0f)
        {
            currentPos += rayDir;

            Vector2i gridPos(static_cast<int>(currentPos.x / CELL_SIZE), static_cast<int>(currentPos.y / CELL_SIZE));

            if (gridPos.x < 0 || gridPos.y < 0 || gridPos.x >= GRID_WIDTH || gridPos.y >= GRID_HEIGHT)
                break;

            Vector2f playerWorldPos = Vector2f(playerPos.x * CELL_SIZE, playerPos.y * CELL_SIZE);
            FloatRect playerBounds(playerWorldPos.x, playerWorldPos.y, CELL_SIZE, CELL_SIZE);

            if (doesSegmentIntersectRectangle(segments[i][0].position, segments[i][1].position, playerBounds, intersection)) {
                segments[i][1].position = intersection;
                hitPlayer = true;

            }

            if (!grid.getCell(gridPos.x, gridPos.y).walkable)
            {
                FloatRect cellBounds(gridPos.x * CELL_SIZE, gridPos.y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

                if (doesSegmentIntersectRectangle(segments[i][0].position, segments[i][1].position, cellBounds, intersection))
                {
                    segments[i][1].position = intersection;
                    hitWall = true;
                }
                break;
            }
        }

        if (hitPlayer && !hitWall) {
            playerInSight = true;
            clock.restart();
        }

        segments[i][0].color = Color::Yellow;
        segments[i][1].color = Color::Yellow;

    }
}

void Enemy::draw(RenderWindow& window)
{

    window.draw(shape);

    Vector2f circleCenter(400, 300);
    float radius = 10;


}

void Enemy::drawCastRay(RenderWindow& window, Grid& grid, const Vector2i& playerPos)
{

    Vector2f direction = getDirection();

    angleRange = 30.f * 3.14159f / 180.0f;
    segmentLength = 150.f;


    updateCastRay(grid, playerPos);
    for (auto& segment : segments) {
        window.draw(segment);
    }
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

bool Enemy::doesSegmentIntersect(Vector2f p1, Vector2f p2, Vector2f q1, Vector2f q2, Vector2f& intersection)
{
    auto cross = [](Vector2f v1, Vector2f v2) {
        return v1.x * v2.y - v1.y * v2.x;
        };

    Vector2f r = p2 - p1;
    Vector2f s = q2 - q1;

    float rxs = cross(r, s);
    float qpxr = cross(q1 - p1, r);

    if (rxs == 0 && qpxr == 0)
        return false;

    if (rxs == 0)
        return false;

    float t = cross(q1 - p1, s) / rxs;
    float u = cross(q1 - p1, r) / rxs;

    if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1))
    {
        intersection = p1 + t * r;
        return true;
    }
    return false;
}

bool Enemy::doesSegmentIntersectRectangle(Vector2f p1, Vector2f p2, FloatRect rect, Vector2f& intersection)
{

    Vector2f topLeft(rect.left, rect.top);
    Vector2f topRight(rect.left + rect.width, rect.top);
    Vector2f bottomLeft(rect.left, rect.top + rect.height);
    Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);

    Vector2f tempIntersection;
    bool hasIntersection = false;
    float minDist = numeric_limits<float>::max();

    auto checkIntersection = [&](Vector2f q1, Vector2f q2) {
        if (doesSegmentIntersect(p1, p2, q1, q2, tempIntersection))
        {
            float dist = hypot(tempIntersection.x - p1.x, tempIntersection.y - p1.y);
            if (dist < minDist)
            {
                minDist = dist;
                intersection = tempIntersection;
                hasIntersection = true;
            }
        }
        };

    checkIntersection(topLeft, topRight);
    checkIntersection(topRight, bottomRight);
    checkIntersection(bottomRight, bottomLeft);
    checkIntersection(bottomLeft, topLeft);

    return hasIntersection;
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
            //cout << x << " " << y << endl;
            vector<Vector2i> testPath = Pathfinding::findPath(grid, getGridPosition(), Vector2i(x, y));
            if (!testPath.empty()) {
                patrolPoints.push_back(Vector2i(x, y));
            }
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
void Enemy::revenge(Objet& objet, Enemy& enemy, Grid& grid, const Vector2i& playerPos, float deltaTime) {
    if (objet.getRecupO() == true) {
        chaseTimer += deltaTime;
        bool fin = true;
        float speed = 200;
        if (chaseTimer<= 15)
        {
            enemy.SetSpeed(speed);
           setCurrentState(CHASE);
           
        }
        else if (chaseTimer > 15)
        {
            speed = 100;
            enemy.SetSpeed(speed);
            objet.setRecupO(fin);
        }
 
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
        currentState = BEHEVIOR;
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

void Enemy::protect(float deltaTime, Grid& grid, const Vector2i& objetPos ) {

    if (path.empty()) {
        setPath(Pathfinding::findPath(grid, getGridPosition(), objetPos));
    }
    moveAlongPath(deltaTime, grid, objetPos);
    
    if (getGridPosition().x <= objetPos.x+5 and getGridPosition().y <= objetPos.y + 5){
        protectTimer += deltaTime;
        if (protectTimer >= 3.0f) {
            setCurrentState(PATROL);
            currentIndexPath = 0;
            path.clear();
            protectTimer = 0.0f;
        }
    }
     
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
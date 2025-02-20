#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Entity.hpp"
#include "Player.hpp"
#include "Pathfinding.hpp"

#include "stdafx.hpp"

class Enemy : public Entity {
public:
    enum State { PATROL, CHASE, SEARCH, PROTECT };
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);

    void setPath(vector<Vector2i> newPath);
    void setTarget(const Vector2i& target);
    void detectPlayer(Grid& grid, const Vector2i& playerPos);
    void update(float deltaTime, Grid& grid, Vector2i& playerPos) override;
    void updateCastRay(Grid& grid,const Vector2i& playerPos);
    void draw(RenderWindow& window);
    void drawCastRay(RenderWindow& window, Grid& grid, const Vector2i& playerPos);
    void moveAlongPath(float deltaTime, Grid& grid, const Vector2i& playerPos);
    State getCurrentState() const { return currentState; }
    State setCurrentState(State Nstate){return currentState = Nstate;}
    sf::RectangleShape& getShape() { return shape; }
    bool doesSegmentIntersect(Vector2f p1, Vector2f p2, Vector2f q1, Vector2f q2, Vector2f& intersection);
    bool doesSegmentIntersectRectangle(Vector2f p1, Vector2f p2, FloatRect rect, Vector2f& intersection);

private:
    State currentState;
    Vector2i gridPosition;
    vector<Vector2i> path;
    vector<Vector2i> searchTargets;

    vector<VertexArray> segments;
    Vector2f circleCenter;
    float moveSpeed = 0.05;
    float angleRange = 30.f * (3.14159f / 180.f); ;
    const int numSegments = 25;
    float segmentLength = 150.f;
    bool playerInSight = false;

    Vector2i lastKnownPlayerPos;
    int currentIndexPath = 0;
    Vector2i targetPosition;
    vector<Vector2i> patrolPoints;
    // champ de vision

    float fovAngle = 45.f;
    float fovDistance = 6.0f;
    float rotationAngle = 0.0f;

    void initPatrol(Grid& grid);
    void chase(Grid& grid, const Vector2i& playerPos, float deltaTime);
    void patrol(float deltaTime, Grid& grid, const Vector2i& playerPos);
    vector<Vector2i> searchPoints(Vector2i lastKnownPos);
    void search(float deltaTime, Grid& grid, const Vector2i& playerPos);

 
    Vector2f getDirection();
    Vector2f castRay(Grid& grid, Vector2f start, float angle);

    Clock clock;
    Time time;
    
};

#endif // ENEMY_HPP
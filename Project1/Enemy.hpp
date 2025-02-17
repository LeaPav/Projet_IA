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

    void setPath(std::vector<sf::Vector2i> newPath);
    void setTarget(const sf::Vector2i& target);
    void detectPlayer(Grid& grid, const sf::Vector2i& playerPos);
    void update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) override;
    void drawFov(RenderWindow& window, Grid& grid);
    void moveAlongPath(float deltaTime, Grid& grid, const Vector2i& playerPos);
   
private:
    State currentState;
    sf::Vector2i gridPosition;
    std::vector<sf::Vector2i> path;
    std::vector<sf::Vector2i> searchTargets;


    sf::Vector2i lastKnownPlayerPos;
    int currentIndexPath = 0;
    sf::Vector2i targetPosition;
    vector<Vector2i> patrolPoints;
    // champ de vision

    float fovAngle = 45.f;
    float fovDistance = 6.0f;
    float rotationAngle = 0.0f;

    void initPatrol(Grid& grid);
    void chase(Grid& grid, const sf::Vector2i& playerPos, float deltaTime);
    void patrol(float deltaTime, Grid& grid, const Vector2i& playerPos);
    std::vector<sf::Vector2i> searchPoints(sf::Vector2i lastKnownPos);
    void search(float deltaTime, Grid& grid, const Vector2i& playerPos);

    bool lineOfSight(Grid& grid, const sf::Vector2i& playerPos);

    Vector2f getDirection();
    Vector2f castRay(Grid& grid, Vector2f start, float angle);
};

#endif // ENEMY_HPP
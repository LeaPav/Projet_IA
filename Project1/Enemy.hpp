#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Entity.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pathfinding.hpp"
#include "Grid.hpp"
#include"Player.hpp"
#include <cmath>
#include <vector>
using namespace sf;
using namespace std;
class Enemy : public Entity {
public:
    Enemy(float x, float y);
    enum State { PATROL, CHASE, SEARCH, PROTECT };
    static constexpr float SPEED = 100.0f;

    sf::Vector2f position;
    std::vector<sf::Vector2i> path;
    int pathIndex;
    sf::Clock moveClock;
    bool needsRepath;
    float detectionRadius;


    void setPath(std::vector<Vector2i> newPath);
    void update(float deltaTime, Grid& grid, RectangleShape& forme) override;
    void patrol(RectangleShape& forme, Grid& grid);
    void search();
    void chase(Vector2f playerPos, RectangleShape& form);
    void protect();
    bool  detectP(Vector2f playerPos, RectangleShape& form);
private:
    
    State currentState;
    Vector2i gridPosition;
    int currentIndexPath = 0;
};

#endif // ENEMY_HPP
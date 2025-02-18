#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "Pathfinding.hpp"
#include "SelctorNode.hpp"
#include <iostream>

class Enemy : public Entity {
public:
    enum State { PATROL, CHASE, SEARCH, PROTECT, BEHEVIOR};
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);

    void setPath(std::vector<sf::Vector2i> newPath);
    void setTarget(const sf::Vector2i& target);
    void detectPlayer(Grid& grid, const sf::Vector2i& playerPos);
    void update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) override;
    void moveAlongPath(float deltaTime, Grid& grid);
    State getCurrentState() const { return currentState; }
    State setCurrentState(State Nstate){currentState = Nstate;}
    sf::RectangleShape& getShape() { return shape; }
    void search(float deltaTime, Grid& grid);
    void protect();
    void chase(Grid& grid, const sf::Vector2i& playerPos, float deltaTime);
    void patrol(float deltaTime, Grid& grid);
private:
    SelectorNode myTree;
    State currentState;
    sf::Vector2i gridPosition;
    std::vector<sf::Vector2i> path;
    std::vector<sf::Vector2i> searchTargets;
    sf::Vector2i lastKnownPlayerPos;
    int currentIndexPath = 0;
    sf::Vector2i targetPosition;

   
    std::vector<sf::Vector2i> searchPoints(sf::Vector2i lastKnownPos);
    
};

#endif // ENEMY_HPP
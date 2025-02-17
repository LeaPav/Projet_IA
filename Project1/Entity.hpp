#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Grid;
class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Entity(float x, float y, sf::Color color);
    virtual ~Entity() = default;
    virtual void update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) = 0;

    virtual sf::Vector2i getGridPosition() const;
};

#endif // ENTITY_HPP
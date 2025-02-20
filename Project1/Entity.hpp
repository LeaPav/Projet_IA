#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "stdafx.hpp"
#include "Grid.hpp"

class Grid;
class Entity {
public:
    RectangleShape shape;
    Vector2f velocity;

    Entity(float x, float y, Color color);
    virtual ~Entity() = default;
    virtual void update(float deltaTime, Grid& grid, Vector2i& playerPos) = 0;

    virtual Vector2i getGridPosition() const;
};

#endif // ENTITY_HPP
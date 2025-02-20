#include "Entity.hpp"

Entity::Entity(float x, float y, Color color) {
    shape.setSize({ 35, 35 });
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

Vector2i Entity::getGridPosition() const
{
    int gridX = static_cast<int>(round(shape.getPosition().x / CELL_SIZE));
    int gridY = static_cast<int>(round(shape.getPosition().y / CELL_SIZE));

    gridX = max(0, min(gridX, GRID_WIDTH - 1));
    gridY = max(0, min(gridY, GRID_HEIGHT - 1));
    return Vector2i(gridX, gridY);
}

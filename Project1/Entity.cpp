#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Color color) {
    shape.setSize({ 35, 35 });
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

sf::Vector2i Entity::getGridPosition() const
{
    int gridX = static_cast<int>(std::round(shape.getPosition().x / CELL_SIZE));
    int gridY = static_cast<int>(std::round(shape.getPosition().y / CELL_SIZE));

    gridX = std::max(0, std::min(gridX, GRID_WIDTH - 1));
    gridY = std::max(0, std::min(gridY, GRID_HEIGHT - 1));
    return sf::Vector2i(gridX, gridY);
}

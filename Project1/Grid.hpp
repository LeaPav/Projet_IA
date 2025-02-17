#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

#include "Entity.hpp"

const int GRID_WIDTH = 25;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 38;

struct Cell {
    bool walkable;
    sf::Vector2f position;
    sf::RectangleShape shape;
};

class Grid {
public:
    Grid();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
   sf::Vector2i playerPosition;
    void setPlayerPosition(const sf::Vector2i& pos);
    Cell& getCell(int x, int y);
    std::vector<std::vector<Cell>> cells;
private:
   
};

#endif      

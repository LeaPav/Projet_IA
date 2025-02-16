#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

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
    Cell& getCell(int x, int y);
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<int>> vGrid;
private:
    
};

#endif      

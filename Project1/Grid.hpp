#ifndef GRID_HPP
#define GRID_HPP

#include "stdafx.hpp"
#include "Entity.hpp"

const int GRID_WIDTH = 48;
const int GRID_HEIGHT = 28;
const int CELL_SIZE = 38;

struct Cell {
    bool walkable;
    Vector2f position;
    RectangleShape shape;
};

class Grid {
public:
    Grid();
    void loadFromFile(const string& filename);
    void draw(RenderWindow& window);
   Vector2i playerPosition;
    void setPlayerPosition(const Vector2i& pos);
    Cell& getCell(int x, int y);
    vector<vector<Cell>> cells;

    bool isWall(Vector2i pos);
private:
   
};

#endif      

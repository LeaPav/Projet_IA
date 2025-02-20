#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Grid.hpp"
#include "Node.hpp"
#include "stdafx.hpp"

class Pathfinding {
public:
    static vector<Vector2i> findPath(Grid& grid, Vector2i start, Vector2i end);
};

#endif
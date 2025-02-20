#ifndef NODE_HPP
#define NODE_HPP

#include "stdafx.hpp"
class Node {
public:
    Vector2i position;
    int gCost, hCost, fCost;
    Node* parent;

    Node(Vector2i pos);
    void calculateCosts(Vector2i endPos, int newG);
    int calculateHeuristic(Vector2i endPos);
};

#endif
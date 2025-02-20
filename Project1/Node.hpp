
#include "stdafx.hpp"

struct Node {
    Vector2i position;
    int gCost, hCost, fCost;
    Node* parent;

    Node(Vector2i pos);
    void calculateCosts(Node* end, int newG);
};
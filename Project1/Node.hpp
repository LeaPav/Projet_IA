#ifndef NODE_HPP
#define NODE_HPP

#include "stdafx.hpp"

struct Node {
    sf::Vector2i position;
    int gCost, hCost, fCost;
    Node* parent;

    Node(sf::Vector2i pos);
    void calculateCosts(Node* end, int newG);
};

#endif
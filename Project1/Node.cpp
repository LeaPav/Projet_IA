#include "Node.hpp"

Node::Node(Vector2i pos) : position(pos), gCost(0), hCost(0), fCost(0), parent(nullptr) {}

void Node::calculateCosts(Node* end, int newG) {
    gCost = newG;
    hCost = abs(position.x - end->position.x) + abs(position.y - end->position.y);
    fCost = gCost + hCost;
}
#include "Node.hpp"

Node::Node(Vector2i pos)
    : position(pos), gCost(0), hCost(0), fCost(0), parent(nullptr) {
}

void Node::calculateCosts(Vector2i endPos, int newG) {
    gCost = newG;
    hCost = calculateHeuristic(endPos);
    fCost = gCost + hCost;
}

int Node::calculateHeuristic(Vector2i endPos) {
    int dx = abs(endPos.x - position.x);
    int dy = abs(endPos.y - position.y);

    return 10 * (dx + dy) + (14 - 2 * 10) * min(dx, dy);
}
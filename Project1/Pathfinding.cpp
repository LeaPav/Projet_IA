#include "Pathfinding.hpp"

vector<Vector2i> Pathfinding::findPath(Grid& grid, Vector2i start, Vector2i end) {
    vector<vector<bool>> visited(GRID_HEIGHT, vector<bool>(GRID_WIDTH, false));
    vector<Node*> openList;
    vector<Node*> allNodes;

    Node* startNode = new Node(start);
    Node* endNode = new Node(end);
    openList.push_back(startNode);
    allNodes.push_back(startNode);

    while (!openList.empty()) {
        sort(openList.begin(), openList.end(), [](Node* a, Node* b) { return a->fCost < b->fCost; });
        Node* current = openList.front();
        openList.erase(openList.begin());

        if (current->position == end) {
            vector<Vector2i> path;
            while (current) {
                path.push_back(current->position);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        visited[current->position.y][current->position.x] = true;

        vector<Vector2i> neighbors = {
            {current->position.x + 1, current->position.y},
            {current->position.x - 1, current->position.y},
            {current->position.x, current->position.y + 1},
            {current->position.x, current->position.y - 1},
          

        };

        bool keepGoing = false;
        for (Vector2i& neighborPos : neighbors) {
            if (neighborPos.x < 0 || neighborPos.x >= GRID_WIDTH || neighborPos.y < 0 || neighborPos.y >= GRID_HEIGHT)
                continue;
            if (!grid.getCell(neighborPos.x, neighborPos.y).walkable || visited[neighborPos.y][neighborPos.x])
                continue;
            for (auto& n : openList) {
                if (n->position == neighborPos) {
                    keepGoing = true;
                    break;
                }
            }
            if (keepGoing)
                continue;

            Node* neighbor = new Node(neighborPos);
            neighbor->parent = current;
            neighbor->calculateCosts(endNode, current->gCost + 1);
            openList.push_back(neighbor);
            allNodes.push_back(neighbor);
        }
    }

    for (Node* node : allNodes)
        delete node;

    return {};
}
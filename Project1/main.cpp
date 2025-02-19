#include "stdafx.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"


const int WINDOW_WIDTH = 835;
const int WINDOW_HEIGHT = 565;

int main() {
    srand((unsigned)time(0));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    Grid grid;
    grid.loadFromFile("map.txt");
    vector<unique_ptr<Enemy>> enemies;

    auto enemy1 = make_unique<Enemy>(100, 100);
    auto enemy2 = make_unique<Enemy>(700, 100);

    enemies.push_back(move(enemy1));
    enemies.push_back(move(enemy2));
    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        
        Vector2i playerGridPos = player.getGridPosition();
        player.update(deltaTime, grid, playerGridPos);
   
        for (auto& enemy : enemies) {
            enemy->update(deltaTime, grid, playerGridPos);
            
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            enemy->draw(window);
           // enemy->drawFov(window, grid);
            enemy->drawCastRay(window, grid, playerGridPos);
        }

        window.display();
    }
    return 0;
}


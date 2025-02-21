#include "stdafx.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"
#include <vector>
#include "Objet.hpp"
#include "Enemy.hpp"
#include "Fsm.hpp"

const int WINDOW_WIDTH = 1785;
const int WINDOW_HEIGHT = 910;

int main() {
 
    srand(unsigned(time(nullptr)));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    Grid grid;
    grid.loadFromFile("map.txt");
    
    
    vector<unique_ptr<Enemy>> enemies;

    auto enemy1 = make_unique<Enemy>(100, 100);
    auto enemy2 = make_unique<Enemy>(1600, 500);
    auto enemy3= make_unique<Enemy>(1100, 800);
    auto enemy4 = make_unique<Enemy>(500, 500);

    Objet objet(496,39.5);
    objet.shape.setFillColor(Color::Yellow);

    enemies.push_back(move(enemy1));
    enemies.push_back(move(enemy2));
    enemies.push_back(move(enemy3));
    enemies.push_back(move(enemy4));
    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        Vector2i objetGridPos = objet.getGridPosition();
        Vector2i playerGridPos = player.getGridPosition();
        player.update(deltaTime, grid, playerGridPos);
        for (auto& enemy : enemies) {
            FSM fsm(*enemy);
            fsm.InitBehevior(*enemy, player);
            fsm.run(deltaTime, grid, playerGridPos, *enemy, objetGridPos,objet);
            enemy->update(deltaTime, grid, playerGridPos);
            
        }
 
        window.clear();
        grid.draw(window);
        
        objet.coliP(player, objet.shape, window);
        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            enemy->draw(window);
            enemy->drawCastRay(window, grid, playerGridPos);
        }

        window.display();
    }
    return 0;
}


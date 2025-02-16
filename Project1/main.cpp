#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include <vector>


const int WINDOW_WIDTH = 835;
const int WINDOW_HEIGHT = 565;
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);
  
    Player player(200, 400);
    std::vector<Enemy> enemies = {Enemy(700, 100) };
    Enemy Enel(100, 100);
    Grid grid;
    grid.loadFromFile("map.txt");
    enemies.push_back(Enel);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.update(deltaTime, grid, player.shape);
       

        window.clear();
        grid.draw(window);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid, enemy.shape);
            window.draw(enemy.shape);
        }
        window.draw(player.shape);
           
        window.display();
    }
    return 0;
}


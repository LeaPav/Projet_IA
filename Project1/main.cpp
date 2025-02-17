#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include <vector>
#include "Objet.hpp"


const int WINDOW_WIDTH = 835;
const int WINDOW_HEIGHT = 565;
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);
  
    Player player(200, 400);
    Grid grid;
    grid.loadFromFile("map.txt");
    std::vector<std::unique_ptr<Enemy>> enemies;

    auto enemy1 = std::make_unique<Enemy>(100, 100);
    auto enemy2 = std::make_unique<Enemy>(700, 100);
    Objet objet(496,39.5);
    objet.shape.setFillColor(Color::Red);
    enemies.push_back(std::move(enemy1));
    enemies.push_back(std::move(enemy2));
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
        objet.coliP(player, objet.shape, window);
        for (auto& enemy : enemies) {
            enemy->update(deltaTime, grid, enemy->shape);
            if (enemy->detectP(player.shape.getPosition(), enemy->shape)) {
                enemy->shape.setFillColor(sf::Color::Magenta);
        }
        else {
                enemy->shape.setFillColor(sf::Color::Green);
        }
            window.draw(enemy->shape);
        }
        window.draw(player.shape);
        
           
        window.display();
    }
    return 0;
}


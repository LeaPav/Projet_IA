#include "Objet.hpp"
Objet::Objet(float x, float y) : Entity(x, y, sf::Color::Red) {}
void Objet::update(float deltaTime, Grid& grid, RectangleShape& forme) {
	forme.setFillColor(Color::Red);
}
void Objet::coliP(Player& player, RectangleShape& forme, RenderWindow& window) {
	if (player.shape.getGlobalBounds().intersects(forme.getGlobalBounds())) {
		cout << "gg";
		recupObj = true;
	}
	if (recupObj == false) {
		window.clear();
		window.draw(forme);
	}

}

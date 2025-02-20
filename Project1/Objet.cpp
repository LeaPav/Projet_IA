#include "Objet.hpp"
Objet::Objet(float x, float y) : Entity(x, y, Color::Red) {}
void Objet::update(float deltaTime, Grid& grid, Vector2i& playerPos) {
	
}
void Objet::coliP(Player& player, RectangleShape& forme, RenderWindow& window) {
	if (player.shape.getGlobalBounds().intersects(forme.getGlobalBounds())) {
		recupObj = true;
		
	}
	if (recupObj == false){
		window.draw(forme);
	}
}

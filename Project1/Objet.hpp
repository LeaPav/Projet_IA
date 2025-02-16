#include"Player.hpp"
#include "Entity.hpp"
#include <iostream>
#include "Pathfinding.hpp"
#include "Grid.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include"Player.hpp"
using namespace sf;
using namespace std;
class Objet :  public Entity{
public:
	
	Objet(float x, float y);
	bool recupObj = false;
	void update(float deltaTime, Grid& grid, RectangleShape& forme) override;
	void coliP(Player& player, RectangleShape& forme, RenderWindow& window);

};
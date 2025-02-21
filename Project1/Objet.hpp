#pragma once
#include"Player.hpp"
#include "Entity.hpp"
#include <iostream>
#include "Grid.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;



class Objet : public Entity{
public:
	
	Objet(float x, float y);

	bool recupObj = false;
	void update(float deltaTime, Grid& grid, Vector2i& playerPos) override;
	void coliP(Player& player, RectangleShape& forme, RenderWindow& window);
	bool getRecupO() const { return recupObj; }
	bool setRecupO(bool recup) { return recupObj = recup; }
};
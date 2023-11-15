#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class HealthPack
{
private:
	// Variables
	sf::CircleShape shape;
	float speed;
	int health;

	// Private functions
	void initVariables();

public:
	// Constructor and Destructor
	HealthPack(float pos_x, float pos_y, sf::Texture* texture);
	virtual ~HealthPack();

	// Accessor
	const sf::FloatRect getBounds() const;
	const int& getHealth() const;

	// Functions
	void update();
	void render(sf::RenderTarget& target);

};


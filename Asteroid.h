#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class Asteroid
{
private:
	// Variables
	sf::CircleShape shape;
	unsigned pointCount;
	float speed;
	int damage;
	int points;

	// Private functions
	void initVariables();
	void initShape();

public:
	// Constructor and Destructor
	Asteroid(float pos_x, float pos_y, sf::Texture* texture);
	virtual ~Asteroid();

	// Accessor
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};


#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Bullet
{
private:
	// Variables
	sf::Sprite shape;
;
	sf::Vector2f direction;
	float movementSpeed;

public:
	// Constructor and Destructor
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	// Accessors
	const sf::FloatRect getBounds() const;

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};


#pragma once

#include<SFML/Graphics.hpp>

class Missile
{
private:
	// Variables
	sf::RectangleShape shape;
	int damage;

	sf::Vector2f direction;
	float movementSpeed;
	sf::Vector2f velocity;

	// Private Functions
	void initVariables();
	void moveTowards(sf::Vector2f playerPos);

public:
	// Constructor and Destructor
	Missile(float pos_x, float pos_y, sf::Texture* texture);
	virtual ~Missile();

	// Accessors
	const sf::FloatRect getBounds() const;
	const int& getDamage() const;

	// Functions
	void update(sf::Vector2f playerPos);
	void render(sf::RenderTarget& target);

};



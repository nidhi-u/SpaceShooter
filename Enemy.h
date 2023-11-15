#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class Enemy
{
private:
	// Variables
	sf::Sprite sprite;
	float pos_x;
	int points;
	int damage;
	float missileTimer;
	float missileTimerMax;

	// Private Functions
	void initVariables();

public:
	// Constructor and Destructor
	Enemy(float pos_x, float pos_y, sf::Texture* texture);
	virtual ~Enemy();

	// Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	const bool& getLaunch();
	const float& getXPos() const;

	// Functions
	void update();
	void render(sf::RenderTarget& target);

};


#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

class Player
{
private:
	// Variables
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCoolDown;
	float attackCoolDownMax;

	int hp;
	int hpMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	
public:
	// Constructor and Destructor
	Player();
	virtual ~Player();

	// Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	// Modifiers
	void setPos(const float x, const float y);
	void setHp(const int hp);

	// Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateCoolDown();
	void update();
	void render(sf::RenderTarget& target);
};


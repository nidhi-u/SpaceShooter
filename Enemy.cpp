#include "Enemy.h"

void Enemy::initVariables()
{
	this->points = 20;
	this->damage = 10;
	this->missileTimerMax = 50.f;
	this->missileTimer = missileTimerMax;
}


Enemy::Enemy(float pos_x, float pos_y, sf::Texture* texture)
{
	this->initVariables();
	
	this->sprite.setTexture(*texture);
	this->sprite.setScale(0.1f, 0.1f);
	this->sprite.setPosition(pos_x, pos_y);
	this->pos_x = pos_x;
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const bool& Enemy::getLaunch()
{
	if (missileTimer >= missileTimerMax)
	{
		missileTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

const float& Enemy::getXPos() const
{
	return this->pos_x;
}

void Enemy::update()
{
	if (this->sprite.getPosition().y < 120)
	{
		this->sprite.move(0.f, 2.f);
	}
	else
	{
		missileTimer += 0.2f;
	}
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

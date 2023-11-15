#include "HealthPack.h"

void HealthPack::initVariables()
{
	this->speed = 2.f;
	this->health = 20;
}

HealthPack::HealthPack(float pos_x, float pos_y, sf::Texture* texture)
{
	this->initVariables();

	this->shape.setRadius(25);
	this->shape.setTexture(texture);
	this->shape.setPosition(pos_x, pos_y);
}

HealthPack::~HealthPack()
{
}

const sf::FloatRect HealthPack::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& HealthPack::getHealth() const
{
	return this->health;
}

void HealthPack::update()
{
	this->shape.move(0.f, this->speed);
}

void HealthPack::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

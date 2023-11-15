#include "Asteroid.h"

// Private functions

void Asteroid::initVariables()
{
	this->pointCount = rand() % 5 + 5;
	this->speed = static_cast<float>(this->pointCount/4);
	this->damage = this->pointCount;
	this->points = 2 * pointCount;
}

void Asteroid::initShape()
{

	this->shape.setRadius(this->pointCount * 5 );
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 75 + 180, rand() % 75 + 180, rand() % 75 + 180, 255));
	this->shape.setRotation(rand() % 360);
}

// Constructor and Destructor
Asteroid::Asteroid(float pos_x, float pos_y, sf::Texture* texture)
{
	this->initVariables();
	this->initShape();

	this->shape.setTexture(texture);

	this->shape.setPosition(pos_x, pos_y);
}

Asteroid::~Asteroid()
{
}

// Accessor
const sf::FloatRect Asteroid::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Asteroid::getPoints() const
{
	return this->points;
}

const int& Asteroid::getDamage() const
{
	return this->damage;
}


// Functions
void Asteroid::update()
{
	this->shape.move(0.f, this->speed);
}

void Asteroid::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

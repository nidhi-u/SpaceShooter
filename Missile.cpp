#include "Missile.h"

void Missile::initVariables()
{
	this->damage = 10;
	this->movementSpeed = 1.5f;
	this->direction.x = 0;
	this->direction.y = 1;
	this->velocity = sf::Vector2f(0.f, 0.f);
}

void Missile::moveTowards(sf::Vector2f playerPos)
{
	this->direction = playerPos - shape.getPosition();
	float length = sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
	if (length != 0)
	{
		this->direction /= length;
	}
	this->velocity = this->movementSpeed * this->direction;

	double pi = 2 * acos(0.0);
	float angle = std::atan2(direction.y, direction.x) * 180 / pi;
	angle += 90;
	shape.setRotation(angle);

}

Missile::Missile(float pos_x, float pos_y, sf::Texture* texture)
{
	this->initVariables();

	this->shape.setSize(sf::Vector2f(10.f, 20.f));
	this->shape.setTexture(texture);
	this->shape.setScale(2.f, 2.f);
	this->shape.setPosition(pos_x, pos_y);
}

Missile::~Missile()
{
}

const sf::FloatRect Missile::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Missile::getDamage() const
{
	return this->damage;
}

void Missile::update(sf::Vector2f playerPos)
{
	this->moveTowards(playerPos);

	this->shape.move(this->velocity);
}

void Missile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

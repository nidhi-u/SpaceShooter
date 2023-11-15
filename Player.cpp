#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 4.f;

	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

// Private Functions
void Player::initTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("Textures/spaceship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file.\n";
	}
}

void Player::initSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	// Resize sprite
	this->sprite.scale(0.17f, 0.17f);
}

// Constructor and Destructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

// Accessor
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

// Modifiers
void Player::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

// Functions
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}

	return false;
}

void Player::updateCoolDown()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
	{
		this->attackCoolDown += 0.5f;
	}

}

void Player::update()
{
	this->updateCoolDown();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}


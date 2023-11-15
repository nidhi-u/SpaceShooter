#include "Game.h"

// Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["Bullet"] = new sf::Texture();
	this->textures["Bullet"]->loadFromFile("Textures/bullet.png");

	this->textures["Asteroid"] = new sf::Texture();
	this->textures["Asteroid"]->loadFromFile("Textures/asteroid.png");

	this->textures["Enemy"] = new sf::Texture();
	this->textures["Enemy"]->loadFromFile("Textures/enemy.png");

	this->textures["Missile"] = new sf::Texture();
	this->textures["Missile"]->loadFromFile("Textures/missile.png");

	this->textures["Health"] = new sf::Texture();
	this->textures["Health"]->loadFromFile("Textures/healthpack.png");

}

void Game::initGUI()
{
	// Load fonts
	if (!this->font.loadFromFile("Fonts/kenpixel.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font";
	}

	// Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("0");
	this->pointText.setPosition(sf::Vector2f(600.f, 20.f));

	// Init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width /2.f, this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	// Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(500.f, 20.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color::White);
}

void Game::initBackground()
{
	if (!this->bgTexture.loadFromFile("Textures/background.png"))
	{
		std::cout << "ERROR::GAME::Could not load background texture" << "\n";
	}
	this->bg.setTexture(this->bgTexture);
	this->bg.scale(2.5f,2.5f);

	this->bg2.setTexture(this->bgTexture);
	this->bg2.scale(2.5f, 2.5f);

	this->bgPos.x = 0;
	this->bgPos.y = 0;
	this->bg2Pos.x = 0;
	this->bg2Pos.y = bgTexture.getSize().y;

	bg.setPosition(bgPos);
	bg2.setPosition(bg2Pos);

	this->bgScrollSpeed = 0.5f;
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPos(this->window->getSize().x/2, this->window->getSize().y - this->player->getBounds().height);
}

void Game::initAsteroids()
{
	this->asteroidSpawnTimerMax = 50.f;
	this->asteroidSpawnTimer = this->asteroidSpawnTimerMax;
}

void Game::initEnemies()
{
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
}

void Game::initHealthPacks()
{
	this->hpSpawnTimer = 0.f;
	this->hpSpawnTimerMax = 100.f;
}

// Constructor and Destructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initBackground();
	this->initSystems();
	this->initPlayer();
	this->initAsteroids();
	this->initEnemies();
	this->initHealthPacks();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	// Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	// Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	// Delete asteroids
	for (auto* i : this->asteroids)
	{
		delete i;
	}

	// Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}

	// Delete missiles
	for (auto* i : this->missiles)
	{
		delete i;
	}

	// Delete healthpacks
	for (auto* i : this->healthpacks)
	{
		delete i;
	}
}

// Functions
void Game::runGame()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0)
		{
			this->update();
			this->render();
		}
	}

}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed || e.KeyPressed && e.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}

	}
}

void Game::updateInput()
{
	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->player->move(0.f, 1.f);
	}

	// Shoot bullet
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(this->textures["Bullet"], 
			this->player->getPos().x + this->player->getBounds().width/2.f, 
			this->player->getPos().y, 
			0.f,
			-1.f, 
			2.f
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	
	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	if (this->player->getHp() > 0)
	{
		float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
		this->playerHpBar.setSize(sf::Vector2f(this->playerHpBarBack.getSize().x * hpPercent, this->playerHpBarBack.getSize().y));
	}
	else
	{
		this->playerHpBar.setSize(sf::Vector2f(0, this->playerHpBar.getSize().y));
	}
}

void Game::updateBackground()
{
	bgPos.y -= bgScrollSpeed;
	bg2Pos.y -= bgScrollSpeed;

	if (bgPos.y <= -(static_cast<int>(bgTexture.getSize().y))) {
		bgPos.y = bgTexture.getSize().y;
	}
	else if (bg2Pos.y <= -(static_cast<int>(bgTexture.getSize().y))) {
		bg2Pos.y = bgTexture.getSize().y;
	}

	bg.setPosition(bgPos);
	bg2.setPosition(bg2Pos);
}

void Game::updatePlayerCollision()
{
	// Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPos(0.f, this->player->getBounds().top);
	}
	// Right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x)
	{
		this->player->setPos(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	// Bottom world collision
	if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y)
	{
		this->player->setPos(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
	// Top world collision
	else if (this->player->getBounds().top < 0.f)
	{
		this->player->setPos(this->player->getBounds().left, 0.f);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		// Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			// Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateAsteroids()
{
	this->asteroidSpawnTimer += 0.5f;
	if (this->asteroidSpawnTimer >= this->asteroidSpawnTimerMax)
	{
		this->asteroids.push_back(new Asteroid(rand() % this->window->getSize().x - 20.f, -100.f, this->textures["Asteroid"]));
		this->asteroidSpawnTimer = 0.f;
	}

	for (int i = 0; i < this->asteroids.size(); i++)
	{
		bool asteroid_removed = false;
		this->asteroids[i]->update();

		for (size_t j = 0; j < this->bullets.size() && !asteroid_removed; j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->asteroids[i]->getBounds()))
			{
				this->points += this->asteroids[i]->getPoints();

				this->bullets.erase(this->bullets.begin() + j);
				this->asteroids.erase(this->asteroids.begin() + i);
				asteroid_removed = true;
			}
		}

		if (!asteroid_removed)
		{
			// Remove asteroids at the bottom of the screen
			if (this->asteroids[i]->getBounds().top > this->window->getSize().y)
			{
				this->asteroids.erase(this->asteroids.begin() + i);
				asteroid_removed = true;
			}
			// Delete asteroid if they collide with player, damage to player
			else if (this->asteroids[i]->getBounds().intersects(this->player->getBounds()))
			{
				this->player->setHp(this->player->getHp() - this->asteroids[i]->getDamage());
				this->asteroids.erase(this->asteroids.begin() + i);
				asteroid_removed = true;
			}

		}

	}
}

void Game::updateEnemies()
{
	this->enemySpawnTimer += 0.05f;
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 50.f, -100.f, this->textures["Enemy"]));
		this->enemySpawnTimer = 0.f;
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->update();
		if (enemies[i]->getLaunch())
		{
			this->missiles.push_back(new Missile(enemies[i]->getXPos() + (enemies[i]->getBounds().width/2), 120.f + enemies[i]->getBounds().height, this->textures["Missile"]));
		}
		bool enemy_removed = false;

		for (size_t j = 0; j < this->bullets.size() && !enemy_removed; j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				this->bullets.erase(this->bullets.begin() + j);
				this->enemies.erase(this->enemies.begin() + i);

				enemy_removed = true;
			}
		}

		if (!enemy_removed)
		{
			if (this->enemies[i]->getBounds().intersects(this->player->getBounds()))
			{
				this->player->setHp(this->player->getHp() - this->enemies[i]->getDamage());
				this->enemies.erase(this->enemies.begin() + i);

				enemy_removed = true;
			}
		}

	}
}

void Game::updateMissiles()
{
	for (int i = 0; i < this->missiles.size(); i++)
	{
		this->missiles[i]->update(this->player->getPos());
		bool missile_removed = false;

		for (size_t j = 0; j < this->bullets.size() && !missile_removed; j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->missiles[i]->getBounds()))
			{
				this->bullets.erase(this->bullets.begin() + j);
				this->missiles.erase(this->missiles.begin() + i);

				missile_removed = true;
			}
		}

		if (!missile_removed)
		{
			if (this->missiles[i]->getBounds().intersects(this->player->getBounds()))
			{
				this->player->setHp(this->player->getHp() - this->missiles[i]->getDamage());
				this->missiles.erase(this->missiles.begin() + i);

				missile_removed = true;
			}
		}
	}
}

void Game::updateHealthPacks()
{
	this->hpSpawnTimer += 0.01f;
	if (this->hpSpawnTimer >= this->hpSpawnTimerMax)
	{
		this->healthpacks.push_back(new HealthPack(rand() % this->window->getSize().x - 20.f, -100.f, this->textures["Health"]));
		this->hpSpawnTimer = 0.f;
	}

	for (int i = 0; i < this->healthpacks.size(); i++)
	{
		bool healthpack_removed = false;
		this->healthpacks[i]->update();

		for (size_t j = 0; j < this->bullets.size() && !healthpack_removed; j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->healthpacks[i]->getBounds()))
			{
				this->bullets.erase(this->bullets.begin() + j);
				this->healthpacks.erase(this->healthpacks.begin() + i);
				healthpack_removed = true;
			}
		}

		if (!healthpack_removed)
		{
			if (this->healthpacks[i]->getBounds().top > this->window->getSize().y)
			{
				this->healthpacks.erase(this->healthpacks.begin() + i);
				healthpack_removed = true;
			}
			else if (this->healthpacks[i]->getBounds().intersects(this->player->getBounds()))
			{
				this->player->setHp(this->player->getHp() + this->healthpacks[i]->getHealth());
				this->healthpacks.erase(this->healthpacks.begin() + i);
				healthpack_removed = true;
			}

		}

	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updatePlayerCollision();

	this->updateBullets();

	this->updateAsteroids();

	this->updateEnemies();

	this->updateMissiles();

	this->updateHealthPacks();

	this->updateGUI();

	this->updateBackground();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);

	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::render()
{
	this->window->clear();

	// Set background
	this->window->draw(this->bg);
	this->window->draw(this->bg2);

	// Draw game
	for (auto *bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	for (auto *asteroid  : this->asteroids)
	{
		asteroid->render(*this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}

	for (auto* missile : this->missiles)
	{
		missile->render(*this->window);
	}

	for (auto* healthpack : this->healthpacks)
	{
		healthpack->render(*this->window);
	}

	this->player->render(*this->window);

	this->renderGUI();

	// Game over screen
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

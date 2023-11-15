#pragma once

#include<map>
#include<string>
#include<sstream>
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Missile.h"
#include "HealthPack.h"

class Game
{
private:
	// Window
	sf::RenderWindow* window;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	// GUI
	sf::Font font;
	sf::Text pointText;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::Text gameOverText;

	// World Background
	sf::Texture bgTexture;
	sf::Sprite bg;
	sf::Sprite bg2;
	sf::Vector2f bgPos;
	sf::Vector2f bg2Pos;
	float bgScrollSpeed;

	// Systems
	unsigned points;

	// Player
	Player* player;

	// Asteroids
	float asteroidSpawnTimer;
	float asteroidSpawnTimerMax;
	std::vector<Asteroid*> asteroids;

	// Enemies
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	std::vector<Enemy*> enemies;

	// Health Packs
	float hpSpawnTimer;
	float hpSpawnTimerMax;
	std::vector<HealthPack*> healthpacks;

	// Missiles
	std::vector<Missile*> missiles;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initBackground();
	void initSystems();
	void initPlayer();
	void initAsteroids();
	void initEnemies();
	void initHealthPacks();

public:
	
	// Constructor and Destructor
	Game();
	virtual ~Game();

	// Functions
	void runGame();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateBackground();
	void updatePlayerCollision();
	void updateBullets();
	void updateAsteroids();
	void updateEnemies();
	void updateMissiles();
	void updateHealthPacks();
	void update();

	void renderGUI();
	void render();
	
};


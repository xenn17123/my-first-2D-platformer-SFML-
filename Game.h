#pragma once
#include <unordered_map>
#include <ctime>
#include <cmath>
#include "Clouds.h"
#include "Enemy.h"
#include "Player.h"
#include "TileMap.h"
#include "Animation.h"
#include "Particles.h"
#include "Bullet.h"



class Game
{

private:

	// basic game things
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	sf::Sprite background;
	float deltaTime;

	// character , tile , etc things
	Player player;
	TileMap tilemap;
	Clouds clouds;

	std::vector<Enemy> vecEnemies;
	std::vector<Player> vecPlayers;
	

	// logic and polishing things (paricles things)
	std::vector<sf::FloatRect> leaf_spawners;
	std::vector<Particles> vecParticlesLeaf;
	std::vector<Particles> vecParticlesparticle;

	std::unordered_map<std::string, std::vector<Particles>> particlesMap;



public:
	std::unordered_map<std::string, std::vector<sf::Texture>> assets;
	std::unordered_map<std::string, Animation> anim_assets;
	
	sf::Vector2f scroll = { 0,0 };
	sf::Vector2f imgPos = { 0,0 };
	sf::Vector2f gridoffset = { 0,0 };
	bool movement[2] = { false, false };



	Game();

	void run();
};


#pragma once
#include "PhysicsEntity.h"
#include <numbers>
#include "utils.h"

class Player : public PhysicsEntity {

private:

	float air_time;
	int jumps;
	bool wall_slide;

	sf::Vector2i respawnPointGridpos;

	std::unordered_map<std::string, std::vector<Particles>>* vecParticlesPointer;



public:
	int dashing = 0;

	float iframesDuration = 1000; // player iframes after being hit in milliseconds
	float iframesTimer = 1000;       // timer for iframes

	sf::FloatRect hitBox;   // FloatRect to be used for collisions


	Player();

	Player(std::unordered_map<std::string, Animation>& anim_assets, sf::Vector2f pos, sf::Vector2f size);

	void update(TileMap& tilemap, sf::Vector2f movement);

	bool jump();

	bool controls();

	bool dash();

	bool damaged(float damage);

	bool die(TileMap& tilemap);

	bool deathResponse(TileMap& tilemap);

	bool respawn(TileMap& tilemap);

	void getAccessToParticlesVector(std::unordered_map<std::string, std::vector<Particles>>& vecPart);

	// return an sf::FloatRect that is to be used for collision with other entities only
	sf::FloatRect getCollisionFloatRect();

	void poolParticles();

	void draw(sf::RenderWindow& window, sf::Vector2f offset);

};
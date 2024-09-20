#pragma once
#include "PhysicsEntity.h"
#include <numbers>
#include "utils.h"

class Enemy : public PhysicsEntity {

private:

	int walking;


	float bulletSpeed = 0;




public:
	Bullet bulletsArray[4];

	sf::Sprite gunSprite;
	sf::Vector2f gunPosOffset = { 0,0 };
	sf::FloatRect hitBox;   // FloatRect to be used for collisions


	Enemy(std::unordered_map<std::string, Animation>& anim_assets, sf::Vector2f pos, sf::Vector2f size);

	void setGun(sf::Texture& gunTexture, sf::Texture& bulletTexture);

	void setGunPosition();

	bool shoot();

	bool die();

	bool deathResponse();

	// return an sf::FloatRect that is to be used for collision with other entities only
	sf::FloatRect getCollisionFloatRect();

	bool checkifCliff(TileMap& tilemap);

	void update(TileMap& tilemap, sf::Vector2f movement);

	void draw(sf::RenderWindow& window, sf::Vector2f offset);
};


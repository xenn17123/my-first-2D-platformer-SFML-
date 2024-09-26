#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "TileMap.h"
#include "VectorMod.h"
#include "Animation.h"
#include "Particles.h"
#include "Bullet.h"

class PhysicsEntity : public sf::Sprite
{

private:

	// texture things
	std::string type;
	sf::Texture* texture;

	Animation animation;

	Tile* tileInCollisionPtr;

	// animation things
	sf::Vector2f anim_offset = {3, 3};
	std::string action;



public: 

	std::unordered_map<std::string, Animation>* anim_assets;
	sf::Clock clock;
	float deltaTime = 0;
	bool isVisible = true;
	bool isActive = true;
	bool isDead = false;
	bool isInvincible = false;    // bool to know if entity is in invincible state
	bool flip;
	float health = 5;
	bool death = false; // true only on the frame when death occurs
	

	// collision things
	bool collisions[4] = { false, false, false, false };

	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::Vector2f worldPos;
	sf::Vector2f worldVelocity;
	sf::Vector2f size;
	sf::Vector2f last_movement;


	PhysicsEntity();

	PhysicsEntity(std::unordered_map<std::string, Animation>& anim_assets, std::string e_type, sf::Vector2f pos, sf::Vector2f size);

	sf::FloatRect getRect();

	Tile* getTileInCollisionPtr();


	void set_action(std::string action);

	void checkCollisions(TileMap& tilemap, sf::Vector2f frameMovement);

	void jump();

	bool damaged(float damage);

	bool die();

	bool deathResponse();

	bool setInactive();

	bool setActive();

	bool Revive();

	sf::Vector2i getGridpos();

	void update(TileMap& tilemap, sf::Vector2f movement);



	void draw(sf::RenderWindow& window, sf::Vector2f offset);



};










#pragma once
#include<SFML/Graphics.hpp>
#include <unordered_map>
#include "TileMap.h"
#include "Tile.h"


class Bullet : public sf::Sprite {

private:


public:

	sf::Vector2f pos;
	sf::Vector2f worldpos;
	sf::Vector2f size;

	float bulletSpeed = 0;
	float lifetimer = 0;
	bool isactive = false;
	bool flip;
	
	Bullet();

	Bullet(sf::Texture& texture);

	void setActive(sf::Vector2f pos, sf::Vector2f worldpos, bool flip);

	void setInactive(sf::Vector2f pos = {100, 100});

	sf::FloatRect getCollisionFloatRect();

	void update(TileMap& tilemap);

	void draw(sf::RenderWindow& window, sf::Vector2f offset);

};

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Spark : sf::ConvexShape
{
private:


public:

	sf::Vector2f pos;
	float angle;
	float speed;
	bool isActive;

	Spark();

	Spark(sf::Vector2f pos, float angle, float speed);

	bool setActive(sf::Vector2f pos);

	bool setActive(sf::Vector2f pos, float angle, float speed);

	bool update();

	void draw(sf::RenderWindow& window, sf::Vector2f offset);

};


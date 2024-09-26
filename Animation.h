#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spark.h"

class Animation
{

private:

	bool loop = true;
	float img_duration = 5;


public:
	std::vector<sf::Texture> images;
	int frame = 0;
	bool done = false;

	Animation();

	Animation(std::vector<sf::Texture> images, float img_dur = 5, bool loop = true);

	Animation getAnimation();

	sf::Texture* img();

	void update();


};


// independant functions for animations and effects

bool InitializeSparks();

Spark* getSparksArray();

int getSparkArraySize();

bool iterateSparksArray(int numOfSparks, sf::Vector2f pos, float angle, float speed);

bool playerDeathAnimation(sf::Vector2f pos);

bool enemyDeathAnimation(sf::Vector2f pos);

bool bulletHitsTileAnimation(sf::Vector2f pos, bool flip);
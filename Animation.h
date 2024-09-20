#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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


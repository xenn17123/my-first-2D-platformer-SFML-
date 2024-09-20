#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <unordered_map>

class Particles
{

private:

	sf::Sprite sprite;

	std::unordered_map<std::string, Animation> anim_assets;

	sf::Vector2f vel;
	int frame = 0;


public:

	sf::Vector2f pos;
	std::string type;

	Animation animation;
	bool kill = false;
	bool isVisible = true;

	//Particles();

	Particles(std::string p_type, sf::Vector2f pos , sf::Vector2f vel, int frame, std::unordered_map<std::string, Animation>& anim_assets);

	void setValues(sf::Vector2f pos, sf::Vector2f vel, int frame);

	void update();

	void draw(sf::RenderWindow& window, sf::Vector2f offset);


};


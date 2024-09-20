#pragma once
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include <random> 
#include <iostream> 


class Cloud : public sf::Sprite
{

private:

	sf::Vector2f pos;
	float speed = 1;
	float depth = 0;


public:

	Cloud();

	Cloud(sf::Vector2f pos, float depth, sf::Texture& texture);

	void update();

	void draw(sf::RenderWindow& window, sf::Vector2f& offset);


};

class Clouds {

private:
	std::vector<Cloud> vecClouds;

public:

	Clouds();

	Clouds(std::unordered_map<std::string, std::vector<sf::Texture>>& assets, int count = 8);

	void update();

	void draw(sf::RenderWindow& window, sf::Vector2f& offset);
};

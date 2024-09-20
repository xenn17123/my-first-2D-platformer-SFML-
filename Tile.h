#pragma once

#include<SFML/Graphics.hpp>
#include <iostream>
#include<unordered_map>
#include "custom/json_nlohmann"
#include "VectorMod.h"

//using json = nlohmann::json;


class Tile : public sf::Sprite
{

private:
	
	//sf::Texture& texture;
	


public:
	sf::Vector2f pos;
	sf::Vector2i gridpos;

	std::string type;
	int variant ;


	Tile();

	Tile(sf::Vector2f pos, std::string e_type, int variant);

	Tile(float pxposx, float pxposy, std::string e_type, int variant);

	void setTileTexture(sf::Texture& texture);


	

};

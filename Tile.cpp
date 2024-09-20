#include "Tile.h"
#include "utils.h"



Tile::Tile() 
{
	//setPosition(pos);
	//setScale(2, 2);
}

Tile::Tile(sf::Vector2f pos, std::string e_type, int variant)
	: gridpos(pos), type(e_type), variant(variant)
{
	//poseditor = { int(pos.x), int(pos.y) };
	this->pos = pos * 32;
	setPosition(this->pos);
	setScale(2, 2);
}

Tile::Tile(float pxposx, float pxposy, std::string e_type, int variant)
	: type(e_type), variant(variant)
{
	this->pos = sf::Vector2f(pxposx, pxposy);
	gridpos = sf::Vector2i(int(this->pos.x), int(this->pos.y));
	setPosition(this->pos);
	setScale(2, 2);
}







void Tile::setTileTexture(sf::Texture& texture)
{
	//this->texture = texture;
	setTexture(texture);


}


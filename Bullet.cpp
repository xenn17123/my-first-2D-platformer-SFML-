#include "Bullet.h"
#include "utils.h"
#include <unordered_map>

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture& texture)
{

	this->setTexture(texture);
	this->pos = { 100, 100 };
	this->size = { float(texture.getSize().x), float(texture.getSize().y) };
	this->setPosition(this->pos);
	this->setScale(2, 2);
	this->size = this->size * this->getScale();
	this->isactive = false;
	
}

void Bullet::setActive(sf::Vector2f pos, sf::Vector2f worldpos, bool flip)
{
	this->flip = flip;
	this->pos = pos + sf::Vector2f(0, 16);
	this->worldpos = worldpos + sf::Vector2f(0, 0);
	if (this->flip) {
		this->setScale(-2, 2);
	}
	else {
		this->setScale(2, 2);
	}

	this->bulletSpeed = this->getScale().x * 2; // for changing direction based on scale and flip

	//appendToBuffer("this was called in setActive function\n");

	this->lifetimer = 0;

	this->isactive = true;
}

void Bullet::setInactive(sf::Vector2f pos)
{
	this->isactive = false;
	this->bulletSpeed = 0;
	this->pos = pos;
	this->setPosition(this->pos);
}

sf::FloatRect Bullet::getCollisionFloatRect()
{
	return sf::FloatRect(this->pos + sf::Vector2f(0, 0), this->size + sf::Vector2f(0, 0));
}

void Bullet::update(TileMap& tilemap)
{

	this->pos.x = this->pos.x + bulletSpeed;
	this->worldpos.x = this->worldpos.x + bulletSpeed;

	// collisions
	//sf::Vector2i gridpos = tilemap.getGridPos(this->worldpos);
	//std::string strpos = tilemap.getGridPosString(gridpos);
	//if (tilemap.ongridTileMap.contains(strpos) == true ) {
	//	if (tilemap.ongridTileMap[strpos].type == "stone" || tilemap.ongridTileMap[strpos].type == "grass") {
	//		this->setInactive();
	//	}

	//}

	char buffer[100];
	sprintf_s(buffer, "lifetimer : %f\n", this->lifetimer); // log buffer
	if(this->isactive)
	//appendToBuffer(buffer);

	if (this->lifetimer > 3000.f) {
		this->setInactive();
	}

	
	this->setPosition(this->pos);
}

void Bullet::draw(sf::RenderWindow& window, sf::Vector2f offset)
{
	this->pos -= offset;
	this->setPosition(this->pos.x + this->size.x * flip, this->pos.y);



	// to make hitbox for bullet
	sf::FloatRect bulleRect(this->getCollisionFloatRect());
	//sf::FloatRect bulleRect(this->getGlobalBounds());
	sf::RectangleShape temp_rect;
	temp_rect.setPosition(bulleRect.getPosition());
	temp_rect.setSize(bulleRect.getSize());
	temp_rect.setFillColor(sf::Color(100, 250, 100, 150));
	temp_rect.setOutlineColor(sf::Color::Green);
	temp_rect.setOutlineThickness(1);
	//getWindowPtr()->draw(temp_rect);

	window.draw(temp_rect);

	
	
	window.draw(*this);
}

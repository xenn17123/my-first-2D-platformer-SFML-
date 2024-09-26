#include "Spark.h"
#include <numbers>

Spark::Spark()
{
	this->setPointCount(4);
	this->pos = sf::Vector2f(0, 0);
	this->angle = 0;
	this->speed = 0;

	this->setPoint(0, sf::Vector2f(0, 0));
	this->setPoint(1, sf::Vector2f(0, 0));
	this->setPoint(2, sf::Vector2f(0, 0));
	this->setPoint(3, sf::Vector2f(0, 0));
}

Spark::Spark(sf::Vector2f pos, float angle, float speed)
	:	pos(pos), angle(angle), speed(speed)
{
	this->isActive = false;
	this->setPointCount(4);


	
	
	this->setPoint(0, sf::Vector2f(0, 0));
	this->setPoint(1, sf::Vector2f(0, 0));
	this->setPoint(2, sf::Vector2f(0, 0));
	this->setPoint(3, sf::Vector2f(0, 0));

}

bool Spark::setActive(sf::Vector2f pos)
{
	this->pos = pos;
	this->isActive = true;

	return true;
}

bool Spark::setActive(sf::Vector2f pos, float angle, float speed)
{
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	this->isActive = true;
	
	return true;
}

bool Spark::update()
{
	if (this->isActive) {
		this->pos.x += std::cos(this->angle) * this->speed;
		this->pos.y += std::sin(this->angle) * this->speed;

		this->speed = std::max(0.f, this->speed - 0.2f);

		this->isActive = bool(this->speed);
		return bool(this->speed);
	}

	return 0;

}

void Spark::draw(sf::RenderWindow& window, sf::Vector2f offset)
{
	//offset.x = -offset.x;
	//offset.y = -offset.y;
	this->pos -= offset;
	if (this->isActive) {
		this->setPoint(0, sf::Vector2f(this->pos.x + std::cos(this->angle) * this->speed * 3 - offset.x, this->pos.y + std::sin(this->angle) * this->speed * 3 - offset.y));
		this->setPoint(1, sf::Vector2f(this->pos.x + std::cos(this->angle + std::numbers::pi * 0.5) * this->speed * 0.5 - offset.x, this->pos.y + std::sin(this->angle + std::numbers::pi * 0.5) * this->speed * 0.5 - offset.y));
		this->setPoint(2, sf::Vector2f(this->pos.x + std::cos(this->angle + std::numbers::pi) * this->speed * 3 - offset.x, this->pos.y + std::sin(this->angle + std::numbers::pi) * this->speed * 3 - offset.y));
		this->setPoint(3, sf::Vector2f(this->pos.x + std::cos(this->angle - std::numbers::pi * 0.5) * this->speed * 0.5 - offset.x, this->pos.y + std::sin(this->angle - std::numbers::pi * 0.5) * this->speed * 0.5 - offset.y));

		window.draw(*this);

	}

}

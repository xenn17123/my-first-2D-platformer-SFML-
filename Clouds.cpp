#include "Clouds.h"
#include "VectorMod.h"
#include "utils.h"

// CLOUD

Cloud::Cloud()
{
}

Cloud::Cloud(sf::Vector2f pos, float depth, sf::Texture& texture)
	: pos(pos), depth(depth)
{
	speed *= depth;
	setTexture(texture);
	setPosition(pos);
	setScale(2, 2);

}

void Cloud::update()
{
	
	pos.x += speed;
	//pos.y += speed;
}

void Cloud::draw(sf::RenderWindow& window, sf::Vector2f& offset)
{
	sf::Vector2f renderPos = pos - offset * depth;
	pos -= offset * depth;
	renderPos.x = int(renderPos.x) % int(window.getSize().x + this->getGlobalBounds().width) - this->getGlobalBounds().width;
	renderPos.y = int(renderPos.y) % int(window.getSize().y + this->getGlobalBounds().height) - this->getGlobalBounds().height;
	if (renderPos.x < -this->getGlobalBounds().width)	pos.x = window.getSize().x + 50;
	if (renderPos.y < -this->getGlobalBounds().height)	pos.y = window.getSize().y + 50;
	setPosition(renderPos);
	window.draw(*this);
}












// CLOUDS

Clouds::Clouds()
{
}

Clouds::Clouds(std::unordered_map<std::string, std::vector<sf::Texture>>& assets, int count)
{

	//std::random_device rd;
	for (int i = 0; i < count; i++) {
		bool cloudt = (rand() % 2 == 1);
		bool cloudA = (rand() % 2 == 1);
		vecClouds.push_back(Cloud(sf::Vector2f(rand() % 960, rand() % 720), 1.f - 0.25f * float(cloudt), assets["clouds"][cloudA]));
	}
}

void Clouds::update()
{
	for (auto& cloud : vecClouds) {
		cloud.update();
	}

}

void Clouds::draw(sf::RenderWindow& window, sf::Vector2f& offset)
{

	for (auto& cloud : vecClouds) {
		//window.draw(cloud);
		cloud.draw(window, offset);
	}
	
}

#include "Particles.h"
#include "utils.h"

//Particles::Particles()
//{
//}

Particles::Particles(std::string p_type, sf::Vector2f pos, sf::Vector2f vel, int frame , std::unordered_map<std::string, Animation>& anim_assets)
	: type(p_type), pos(pos), vel(vel), frame(frame), anim_assets(anim_assets)
{
	animation = this->anim_assets["particles/" + type];
	animation.frame = frame;
	this->sprite.setScale(2, 2);
	
}

void Particles::setValues(sf::Vector2f pos, sf::Vector2f vel, int frame)
{
	this->pos = pos;
	sprite.setPosition(this->pos);
	this->vel = vel;
	this->frame = frame;
	this->animation.frame = frame;
	this->kill = false;
	this->animation.done = false;
	this->isVisible = true;
}

void Particles::update()
{

	kill = false;
	if (this->animation.done) {
		kill = true;
	}

	this->pos.x += this->vel.x;
	this->pos.y += this->vel.y;
	sprite.setPosition(this->pos);

	this->animation.update();


}

void Particles::draw(sf::RenderWindow& window, sf::Vector2f offset)
{

	this->pos -= offset;

	if (isVisible) {

		sprite.setPosition(pos);
		sprite.setTexture(*this->animation.img());
		window.draw(sprite);
	}

}



#include "Player.h"
#include "utils.h"





Player::Player()
{
}

Player::Player(std::unordered_map<std::string, Animation>& anim_assets, sf::Vector2f pos, sf::Vector2f size)
	: PhysicsEntity(anim_assets, "player", pos, size)
{
	this->air_time = 0;
	this->jumps = 2;
	this->wall_slide = false;
	this->health = 1;
	this->respawnPointGridpos = getGridposCalculated(this->worldPos);

}

void Player::update(TileMap& tilemap, sf::Vector2f movement)
{

	death = false;
	if (isDead) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->isDead = false;
			this->respawn(tilemap);
		}
	}

	if (this->isActive) {

		std::string temp_pos = getgridposString(this->getGridpos().x, this->getGridpos().y);

		char buffer[100];
		sprintf_s(buffer, "player world px position  = (%.1f, %.1f), \"%s\" \n", this->worldPos.x, this->worldPos.y, temp_pos.c_str());
		//appendToBuffer(buffer);

		char buffer1[100];
		sprintf_s(buffer1, "player spawn pos= (%i, %i),\n", this->respawnPointGridpos.x, this->respawnPointGridpos.y);
		//appendToBuffer(buffer1);

		// set animation
		this->air_time += 1;

		if (this->collisions[3]) {
			this->air_time = 0;
			this->jumps = 2;
		}

		this->wall_slide = false;
		if ((collisions[0] || collisions[1]) && this->air_time > 4) { // if wall sliding
			this->wall_slide = true;

			if (this->collisions[1])
				this->flip = false;
			else
				this->flip = true;
			set_action("wall_slide");

			this->velocity.y = std::min(this->velocity.y, 3.f);
		}
		else if (!wall_slide) {

			if (this->air_time > 4)		set_action("jump");
			else if (movement.x != 0)	set_action("run");
			else						set_action("idle");
		}


		if (abs(this->dashing) == 50 || abs(this->dashing) == 60) { // for effects
		}

		// runs on start and end of dash
		if (abs(this->dashing) == 50 || abs(this->dashing) == 60) {
			for (int i = 0, b = 0; i < (*vecParticlesPointer)["particle"].size() && b < 20; i++) { // burst of particles

				if (!(*vecParticlesPointer)["particle"][i].isVisible) {
					float angle = randrangefloat(0, 1) * 3.1415f * 2;
					float speed = randrangefloat(0, 1) * 0.5 + 1.0f;
					sf::Vector2f pvelocity = { std::cos(angle) * speed, std::sin(angle) * speed };
					(*vecParticlesPointer)["particle"][i].setValues(this->getRect().getPosition(), pvelocity, randrangeint(0, 1));
					b++;
				}

			}
		}

		this->isVisible = true;

		//dash movement
		if (dashing > 0)	this->dashing = std::max(0, dashing - 1);  // approach zero
		if (dashing < 0)	this->dashing = std::min(0, dashing + 1);  // approach zero


		// while dashing code (this will run while dashing only)
		if (abs(this->dashing) > 50) {

			this->isVisible = false; // make player invisible

			this->velocity.x = (abs(dashing) / dashing) * 16;

			if (abs(dashing) == 51) { // dash ending code
				this->velocity.x *= 0.1; // stops dashing by reducing velocity
			}

			sf::Vector2f pvelocity = { abs(this->dashing) / this->dashing * randrangefloat(0,1) * 3, 0 };

			// dashing trail particle code here
			for (int i = 0; i < (*vecParticlesPointer)["particle"].size(); i++) {
				if (!(*vecParticlesPointer)["particle"][i].isVisible) {  // make changes here - setValues funstion is to be calles here
					(*vecParticlesPointer)["particle"][i].setValues(this->getRect().getPosition(), pvelocity, randrangeint(0, 7));
					break;
				}
			}
		}

		// iframes timer updates
		if (this->iframesTimer <= 0) {
			isInvincible = false;
		}
		else if (this->iframesTimer > 0) {
			isInvincible = true;
			this->iframesTimer -= this->deltaTime;
		}


		if (velocity.x < 0)  velocity.x = std::min(velocity.x + 0.2f, 0.f); // x speed approaces 0
		if (velocity.x > 0)	 velocity.x = std::max(velocity.x - 0.2f, 0.f); // x speed approaces 0

		PhysicsEntity::update(tilemap, movement);
		
		// die
		if (this->health <= 0 && this->isDead == false) {
			this->die(tilemap);
			death = true;
			//appendToBuffer("player just died\n");
		}



	} // isActive condition
	


}

bool Player::jump()
{

	if (this->wall_slide) { // wall jump
		if (this->flip && this->last_movement.x < 0) { // faceLeft
			this->velocity.x = 6;
			this->velocity.y = -10;
			this->air_time = 5;
			this->jumps = std::max(0, this->jumps - 1);

		}
		else if (!this->flip && this->last_movement.x > 0) { // faceRight
			this->velocity.x = -6;
			this->velocity.y = -10;
			this->air_time = 5;
			this->jumps = std::max(0, this->jumps - 1);
		}
		return true;
	}

	else if (this->jumps) {  // ground jump
		this->velocity.y = -10;
		this->jumps -= 1;
		this->air_time = 5;
		return true;
	}


	return false;
}

bool Player::controls()
{



	return false;
}

bool Player::dash()
{
	if (!this->dashing) {
		if (this->flip)	this->dashing = -60;
		else			this->dashing = 60;

		return true;
	}


	return false;
}

bool Player::damaged(float damage)
{
	return PhysicsEntity::damaged(damage);

	return false;
}

bool Player::die(TileMap& tilemap)
{
	this->isDead = true;
	this->setInactive();
	//appendToBuffer("dies\n");
	this->deathResponse(tilemap);
	return false;
}

bool Player::deathResponse(TileMap& tilemap)
{
	playerDeathAnimation(this->pos); // death animations
	//this->respawn(tilemap);
	return false;
}

bool Player::respawn(TileMap& tilemap)
{
	this->health = 2;
	this->velocity = { 0,0 };
	this->dashing = 0;
	this->worldPos = { float(this->respawnPointGridpos.x * 32)  , float(this->respawnPointGridpos.y * 32) };
	this->pos = worldPos - tilemap.gridOffset;
	this->isDead = false;
	this->setActive();
	return true;
}

void Player::getAccessToParticlesVector(std::unordered_map<std::string, std::vector<Particles>>& vecPart)
{
	vecParticlesPointer = &vecPart;
}

void Player::poolParticles()
{
	for (int i = 0; i < 60; i++) {
		Particles P("particle", sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0, *anim_assets);
		P.isVisible = false;
		(*vecParticlesPointer)["particle"].push_back(P);

	}
}

void Player::draw(sf::RenderWindow& window, sf::Vector2f offset)
{
	//this->worldPos += offset;
	PhysicsEntity::draw(window, offset);


	sf::RectangleShape rect;
	//rect.setPosition(this->getGlobalBounds().getPosition());
	rect.setPosition(this->getCollisionFloatRect().getPosition());
	//rect.setPosition(this->pos);
	//rect.setSize(this->getGlobalBounds().getSize());
	rect.setSize(this->getCollisionFloatRect().getSize());
	//rect.setSize(this->size);
	rect.setFillColor(sf::Color(100, 200, 100, 200));
	rect.setOutlineThickness(1);
	window.draw(rect);

}

sf::FloatRect Player::getCollisionFloatRect()
{
	return sf::FloatRect(this->pos + sf::Vector2f(6, 5), this->size + sf::Vector2f(-13, -5));
}

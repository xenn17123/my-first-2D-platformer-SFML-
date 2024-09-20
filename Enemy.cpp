#include "Enemy.h"
#include "utils.h"




Enemy::Enemy(std::unordered_map<std::string, Animation>& anim_assets, sf::Vector2f pos, sf::Vector2f size)
	: PhysicsEntity(anim_assets, "enemy", pos, size)
{
	this->walking = 0;
	this->flip = bool(rand() % 2);
	this->worldPos += sf::Vector2f(0, 0);
	this->health = 1;
}


void Enemy::setGun(sf::Texture& gunTexture, sf::Texture& bulletTexture)
{
	gunSprite.setTexture(gunTexture);
	gunSprite.setPosition(this->pos + gunPosOffset);
	gunSprite.setScale(this->getScale());

	int temp_size = sizeof(bulletsArray) / sizeof(bulletsArray[0]);

	for (int i = 0; i < temp_size; i++) {
		bulletsArray[i] = Bullet(bulletTexture);
	}

}

sf::FloatRect Enemy::getCollisionFloatRect()
{
	return sf::FloatRect(this->pos + sf::Vector2f(6, 5), this->size + sf::Vector2f(-13, -5));
}

void Enemy::setGunPosition()
{

	if (this->flip) {
		gunPosOffset = sf::Vector2f(4, 21);
		gunSprite.setScale(-2, 2);
	}
	else {
		gunPosOffset = sf::Vector2f(20, 21);
		gunSprite.setScale(2, 2);
	}
	this->pos;
	gunSprite.setPosition(this->pos + gunPosOffset);

}

bool Enemy::shoot()
{
	int temp_size = sizeof(bulletsArray) / sizeof(bulletsArray[0]);
	for (int i = 0; i < temp_size; i++) {
		if (this->bulletsArray[i].isactive) {
			continue;
		}
		else {
			this->bulletsArray[i].setActive(this->pos, this->worldPos, this->flip);
			break;
		}
	}
	return true;
}

bool Enemy::die()
{

	this->deathResponse();
	return false;
}

bool Enemy::deathResponse()
{
	this->setInactive();
	return false;
}


bool Enemy::checkifCliff(TileMap& tilemap)
{

	// check if cliff
	std::string temp_pos = getgridposString(this->getGridpos().x, this->getGridpos().y);

	char buffer[100];
	sprintf_s(buffer, "enemy world px position  = (%.1f , %.1f) , \"%s\" \n", this->worldPos.x, this->worldPos.y, temp_pos.c_str());
	//appendToBuffer(buffer);

	temp_pos = getgridposString(this->getGridpos().x - 1, this->getGridpos().y + 1); // bottom-left  tile check
	//std::cout << temp_pos  << "\n";
	if (!tilemap.ongridTileMap.contains(temp_pos)) {
		this->flip = false;
		return true;
	}
	temp_pos = getgridposString(this->getGridpos().x + 1, this->getGridpos().y + 1); // bottom-right tile check 
	//std::cout << temp_pos << "\n";
	if (!tilemap.ongridTileMap.contains(temp_pos)) {
		this->flip = true;
		return true;
	}

	// check if wall
	if (this->collisions[0] || this->collisions[1]) {
		this->flip = !this->flip;
		return true;
	}


	return 0;

}

void Enemy::update(TileMap& tilemap, sf::Vector2f movement)
{

	if (isActive) {
		this->checkifCliff(tilemap);

		if (this->walking) {
			movement.x += (this->flip == false ? 1 : -1);
			this->walking -= 1;
			if (this->walking == 0) { // the frame on which the enmey stops
				this->shoot();

				appendToBuffer("shot by enemy\n");
			}
		}
		else if (randrangeint(0, 100) == 1) { // 1 in 100 chance per frame
			this->walking = randrangeint(60, 120);
		}

		PhysicsEntity::update(tilemap, movement);


		

		if (movement.x == 0)		set_action("idle");
		else						set_action("run");
	}
	int temp_size = sizeof(bulletsArray) / sizeof(bulletsArray[0]);
	for (int i = 0; i < temp_size; i++) {
		this->bulletsArray[i].update(tilemap); // update bullets
		this->bulletsArray[i].lifetimer += this->deltaTime; // update timer of a bullet
	}

	this->setGunPosition();
}

void Enemy::draw(sf::RenderWindow& window, sf::Vector2f offset)
{

	PhysicsEntity::draw(window, offset);

	if (this->isActive) {
		window.draw(gunSprite);
	}


	int temp_size = sizeof(bulletsArray) / sizeof(bulletsArray[0]);
	for (int i = 0; i < temp_size; i++) {
		if (bulletsArray[i].isactive) {
			bulletsArray[i].draw(window, offset);
		}
	}

	bool showHitBoxes = this->isActive;

	if (showHitBoxes) {
		sf::RectangleShape rect;
		rect.setPosition(this->getCollisionFloatRect().getPosition());
		//rect.setPosition(this->getGlobalBounds().getPosition());
		//rect.setPosition(this->pos);
		rect.setSize(this->getCollisionFloatRect().getSize());
		//rect.setSize(this->size);
		rect.setFillColor(sf::Color(200, 100, 100, 200));
		rect.setOutlineThickness(1);
		window.draw(rect);
	}

}

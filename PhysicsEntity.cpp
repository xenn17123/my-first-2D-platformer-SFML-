#include "PhysicsEntity.h"
#include <numbers>
#include "utils.h"

PhysicsEntity::PhysicsEntity()
{

}


// mainly using this one
PhysicsEntity::PhysicsEntity(std::unordered_map<std::string, Animation>& anim_assets , std::string e_type, sf::Vector2f pos, sf::Vector2f size)
{
	this->type = e_type;
	this->pos = pos;
	this->anim_assets = &anim_assets;
	//this->worldPos = pos + sf::Vector2f(16, -32); // position was off by this much for some reason (its not perfect but good for now)
	this->worldPos = pos + sf::Vector2f(10,20); // position was off by this much for some reason (seems perfect to me) 

	setPosition(this->pos);
	//setTexture(texture);
	setScale(2, 2);
	this->size = size * getScale();
	
	this->flip = false;

	this->health = 2;

	set_action("idle");

	

}


sf::FloatRect PhysicsEntity::getRect() // colliderect of physics entity
{

	return sf::FloatRect({this->pos, this->size - sf::Vector2f(0  , 0)});
}

Tile* PhysicsEntity::getTileInCollisionPtr()
{

	return tileInCollisionPtr;
}

void PhysicsEntity::set_action(std::string action)
{
	if (action != this->action) {
		this->action = action;
		this->animation = (*anim_assets)[this->type + "/" + this->action].getAnimation();
	}
}

void PhysicsEntity::checkCollisions(TileMap& tilemap, sf::Vector2f frameMovement)
{

	tilemap.TilesNearby.clear();

	for (auto& tile : tilemap.ongridTileMap) { // this for loop put nearby tiles to a vector container TilesNearby
		if (tile.second.type == "stone" || tile.second.type == "grass") {

			tile.second.setColor(sf::Color(255, 255, 255));
			sf::FloatRect rect = tile.second.getGlobalBounds();
			float dx = (this->pos.x + this->size.x / 2) - (rect.left + rect.width / 2);
			float dy = (this->pos.y + this->size.y / 2) - (rect.top + rect.height / 2);

			float distance = sqrt(dx * dx + dy * dy);

			if (distance < this->size.y * 2) {
				tile.second.setColor(sf::Color(0, 255, 255));
				tilemap.TilesNearby.push_back(&tile.second);

				this->tileInCollisionPtr = &tile.second; // stores current tile pointer thats in collsion;
			}
		}
	}


	// collisions for x-axis
    this->pos.x += frameMovement.x;
	
	sf::FloatRect playerRect = this->getRect();
	for (auto& tile : tilemap.TilesNearby) {  
		//tile->setColor(sf::Color(0, 255, 255));

		if (playerRect.intersects(tile->getGlobalBounds())) {

            
			if (frameMovement.x < 0) { // left  // player.left = tile.right
                playerRect.left = tile->getPosition().x + tile->getGlobalBounds().width;
				//printf("pushed right\n");
                collisions[0] = true;
            }
            if (frameMovement.x > 0) { // right // player.right = tile.left
                playerRect.left = tile->getPosition().x - playerRect.width;
                collisions[1] = true;
				//printf("pushed left\n");
            }
            this->pos.x = playerRect.left; // assign modified frect pos
		}
	}


	// collisions for y-axis
    this->pos.y += frameMovement.y;

	sf::FloatRect playerRect1 = this->getRect();
    for (auto& tile : tilemap.TilesNearby) {
        //tile->setColor(sf::Color(0, 255, 255));

        if (playerRect1.intersects(tile->getGlobalBounds())) {

            if (frameMovement.y < 0) { // top  // player.top = tile.down
                playerRect1.top = tile->getPosition().y + tile->getGlobalBounds().height;
                collisions[2] = true;
				//printf("pushed down\n");
            }
            if (frameMovement.y > 0) { // down// player.down = tile.top
                playerRect1.top = tile->getPosition().y - playerRect1.height;
                collisions[3] = true;
				//printf("pushed up\n");
            }
			this->pos.y = playerRect1.top; // assign modified frect pos
        }
    }

	

}

void PhysicsEntity::jump()
{

}


void PhysicsEntity::update(TileMap& tilemap, sf::Vector2f movement)
{
	this->deltaTime = clock.restart().asMilliseconds();

	if (isActive) {
		for (int i = 0; i < 4; i++) {
			collisions[i] = false;
		}

		velocity.y = std::min(10.f, velocity.y + 0.3f); //   GRAVITY, cap velocity.y to 10

		sf::Vector2f frameMovement = movement + velocity;

		sf::Vector2f temp_prev_pos = this->pos;

		this->checkCollisions(tilemap, frameMovement);

		sf::Vector2f temp_change_pos = this->pos - temp_prev_pos;


		if (movement.x > 0)  flip = false;
		else if (movement.x < 0)  flip = true;
	
		this->last_movement = movement;
		if (collisions[2] || collisions[3]) { // y axis
			this->velocity.y = 0;
			frameMovement.y = 0;
		}
		if (collisions[0] || collisions[1]) { // x axis
			frameMovement.x = 0;
			movement.x = 0;
		}

		animation.update();

		this->worldPos += temp_change_pos; // change in position is added to worldpos

		if (this->health <= 0) {
			this->health = 0;
			this->die();
		}

		this->setPosition(this->pos); // position is set

	}

}

sf::Vector2i PhysicsEntity::getGridpos()
{
	int x = this->worldPos.x / 32;
	int y = this->worldPos.y / 32;
	if (this->worldPos.x < 0)	x--;
	if (this->worldPos.y < 0)	y--;
	//sf::Vector2f  p = this->worldPos / 32;
	
	return sf::Vector2i(x, y);
}

void PhysicsEntity::draw(sf::RenderWindow& window, sf::Vector2f offset)
{
	
	this->pos -= offset;
	
	// flip
	if (flip)
		setScale(-2, 2);
	else
		setScale(2, 2);

	this->setPosition(this->pos.x + (this->size.x) * flip, this->pos.y); // adjusr position changed after changing scale

	if (isActive) {
		
		setTexture(*animation.img());

		if (this->isVisible) {
			window.draw(*this);
		}

	}
	

}

bool PhysicsEntity::die()
{
	this->deathResponse();
	return false;
}

bool PhysicsEntity::damaged(float damage)
{
	if (!this->isInvincible) {

		this->health -= damage;

		return true;
	}
	else {
		return false;
	}

	return false;
}

bool PhysicsEntity::deathResponse()
{
	this->setInactive();
	return false;
}

bool PhysicsEntity::setInactive()
{
	isActive = false;
	return false;
}

bool PhysicsEntity::setActive()
{
	isActive = true;
	return false;
}



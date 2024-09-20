#include "Collisions.h"
#include "utils.h"

//bool checkCollision_aabb(sf::FloatRect& rect1, sf::FloatRect& rect2)
//{
//	if (rect1.intersects(rect2))	return true;
//
//	return false;
//}

bool checkCollision_aabb(sf::FloatRect rect1, sf::FloatRect rect2)
{
	return rect1.intersects(rect2);
}

bool checkCollision_Bullet_Solid(Bullet& bullet, Tile& tile)
{
	if (getGridposCalculated(bullet.worldpos) == (tile.gridpos))	return true;
	
	return false;
}

bool checkCollision_Bullet_Player(Bullet& bullet, Player& player)
{
	sf::FloatRect bulletRect(bullet.getGlobalBounds());
	sf::FloatRect playerRect(player.getGlobalBounds());

	return checkCollision_aabb(playerRect, bulletRect);
}

//return true if a player and an enemy are colliding
bool checkCollision_Player_Enemy(Player& player, Enemy& enemy)
{
	return checkCollision_aabb(player.getCollisionFloatRect(), enemy.getCollisionFloatRect());
}

bool checkCollision_Bullet_Enemy(Bullet& bullet, Enemy& enemy)
{
	return false;
}

bool Collision_Tilemap_PhysicsEntity(TileMap& tilemap, PhysicsEntity& entity)
{
	
	return false;
}

bool collisionResponse_Bullet_SolidTile(Bullet& bullet, Tile& tile)
{
	return false;
}

bool collisionResponse_Bullet_Player(Bullet& bullet, Player& player)
{
	
	if (!player.isInvincible) {
		player.health--;
		player.iframesTimer = player.iframesDuration;

		char buffer[50];
		sprintf_s(buffer, "player health = %.2f \n", player.health);
		appendToBuffer(buffer);
	}
	
	return false;
}

bool collisionResponse_Bullet_Enemy(Bullet& bullet, Enemy& enemy)
{
	return false;
}

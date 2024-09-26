#pragma once
#include<SFML/Graphics.hpp>
#include "TileMap.h"
#include "Tile.h"
#include "Bullet.h"
#include "PhysicsEntity.h"
#include "Enemy.h"
#include "Player.h"

// sf::FloatRect::intersects is called here
bool checkCollision_aabb(sf::FloatRect rect1, sf::FloatRect rect2);

// bullet and tile collision
bool checkCollision_Bullet_SolidTile(Bullet& bullet, TileMap& tilemap);

// bullet and player collision
bool checkCollision_Bullet_Player(Bullet& bullet, Player& player);

// player and enemy collision
bool checkCollision_Player_Enemy(Player& player, Enemy& enemy);

// bullet and enemy collision
bool checkCollision_Bullet_Enemy(Bullet& bullet, Enemy& enemy);

// PhysicsEntity and tilemap
bool Collision_Tilemap_PhysicsEntity(TileMap& tilemap, PhysicsEntity& entity);





bool collisionResponse_Bullet_SolidTile(Bullet& bullet, TileMap& tilemap);

bool collisionResponse_Bullet_Player(Bullet& bullet, Player& player);

bool collisionResponse_Bullet_Enemy(Bullet& bullet, Enemy& enemy);


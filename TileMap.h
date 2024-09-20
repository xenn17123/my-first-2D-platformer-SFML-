#pragma once
#include<SFML/Graphics.hpp>
#include "Tile.h"


class TileMap
{

private:



public:
	int tileSize = 32; // grid will be square 

	sf::Vector2f gridOffset = { 0,0 };

	std::vector<Tile> vecTiles;
	std::vector<Tile*> TilesNearby;

	std::unordered_map<std::string, Tile> ongridTileMap;

	std::vector<Tile> offgridTilemap;

	TileMap(int tileSize = 32);

	void setMap(std::unordered_map<std::string, std::vector<sf::Texture>>& assets);

	std::vector<Tile> extract(std::string T_type, int variant, bool keep = false);

	std::vector<Tile*> tiles_around(sf::Vector2i loc);

	sf::Vector2i getGridPos(sf::Vector2f pos);

	std::string getGridPosString(sf::Vector2i pos);

	std::string getTileStringGridLoc(Tile* tile);

	void saveMap(std::string path);

	void loadMap(std::string path, std::unordered_map<std::string, std::vector<sf::Texture>>& assets);

	void draw(sf::RenderWindow& window, sf::Vector2f offset);

	



};


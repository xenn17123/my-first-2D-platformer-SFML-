#pragma once
#include <unordered_map>
#include <ctime>
#include "TileMap.h"
#include "utils.h"
#include <fstream>
#include <custom/json_nlohmann>
#include "VectorMod.h"

class Editor
{
private:


	sf::RenderWindow window;
	sf::Clock clock;
	sf::Event event;
	sf::Sprite background;


	TileMap tilemap;

	bool gridSelected = true;

	sf::Vector2f gridoffset = { 0,0 }; 

	// time timers declared
	float CameraLeftMovementTimer  = 0;
	float CameraRightMovementTimer = 0;
	float CameraUpMovementTimer    = 0;
	float CameraDownMovementTimer = 0;

public:
	std::unordered_map<std::string, std::vector<sf::Texture>> assets;
	std::vector<std::string> vecTile_list;
	int tile_group;
	int tile_variant;

	sf::Vector2f scroll = { 0,0 };
	sf::Vector2f imgPos = { 0,0 };
	bool movement[2] = { false, false };



	Editor();

	void drawGrid(sf::Vector2f offset, int tileSize = 32);

	void run();
};

// vscode lib
//C:\mingw32\include\c++\13.1.0\iostream

// VS lin
//C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519\include\iostream

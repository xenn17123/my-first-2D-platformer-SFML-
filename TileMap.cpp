#include "TileMap.h"
#include <fstream>
#include "utils.h"


// to_nlohmann::json and from_nlohmann::json functions are defined
static void to_json(nlohmann::json& j, const Tile& t) {
	j = nlohmann::json{
		{"pos", {int(t.pos.x), int(t.pos.y)}},
		//{"pos", {int(t.pos.x / 32), int(t.pos.y / 32)}},
		//{"pos", {t.poseditor.x , t.poseditor.y }},
		{"type", t.type},
		{"variant", t.variant}
	};
}
static void from_json(const nlohmann::json& j, Tile& t) {
	// Extract the position as sf::Vector2i
	float x = j.at("pos").at(0);
	float y = j.at("pos").at(1);

	//t.pos = sf::Vector2f(float(x), float(y));
	t.pos = sf::Vector2f(x, y);
	//t.pos = sf::Vector2f(x * 32, y * 32);

	// Extract the type and variant
	j.at("type").get_to(t.type);
	j.at("variant").get_to(t.variant);
}


TileMap::TileMap(int tileSize)
{
	this->tileSize = tileSize;

}



void TileMap::setMap(std::unordered_map<std::string, std::vector<sf::Texture>>& assets)
{
	for (int i = 6; i < 19; i++) {
		std::string locH = (std::to_string(i + 8) + ';' + std::to_string(10)); // position strings, seperate because too long
	}
}

std::vector<Tile>TileMap::extract(std::string T_type, int variant, bool keep)
{
	std::vector<Tile> matches ; // vector to return
		
	for (auto& tilePair : ongridTileMap) { // loop throught main Tile container
		if (tilePair.second.type == T_type && tilePair.second.variant == variant) {  // if type of tile matches
			matches.push_back(tilePair.second);

			if (!keep) {
				//delete& tilePair;
				ongridTileMap.erase(tilePair.second.type);

			}
		}
	}

	for (auto tile = offgridTilemap.begin() ; tile != offgridTilemap.end();) {
		if (tile->type == T_type && tile->variant == variant) {
			matches.push_back(*tile);

			if (!keep) {
				tile = offgridTilemap.erase(tile);
				tile--;
			}
		}
		tile++;
	}


	return matches;
}

std::vector<Tile*> TileMap::tiles_around(sf::Vector2i loc)
{
	return std::vector<Tile*>();
}

sf::Vector2i TileMap::getGridPos(sf::Vector2f pos)
{
	int x = pos.x / 32;
	int y = pos.y / 32;
	if	(pos.x < 0)	x--;
	if	(pos.y < 0)	y--;

	return sf::Vector2i(x, y);
	
}

std::string TileMap::getGridPosString(sf::Vector2i pos)
{
	return std::string(std::to_string(pos.x) + ";" + std::to_string(pos.y));
}

std::string TileMap::getTileStringGridLoc(Tile* tile)
{
	//std::string loc = std::to_string(tile->gridpos.x) + ";" + std::to_string(tile->gridpos.y);
	//return loc;
	return std::string();
}



void TileMap::saveMap(std::string path)
{
	printf("saving this to nlohmann::json file:\n\n\n");
	nlohmann::json j; //  { "ongridtilemap": {Tiles}, "tilesize" : int , "offgrid" : {Tiles} };

	std::vector<Tile> temp_offgridTilemap = offgridTilemap;
	for (auto& tile : temp_offgridTilemap) {
		//tile.pos = tile.pos * 2;
	}
	std::unordered_map<std::string, Tile> temp_ongridTileMap = ongridTileMap;
	for (auto& tile : temp_ongridTileMap) {
		tile.second.pos = tile.second.pos / 32;
	}


	j["tilemap"] = temp_ongridTileMap;
	j["tile_size"] = tileSize;
	j["offgrid"] = temp_offgridTilemap;


	std::ofstream file;
	file.open(path), std::ios::out;
	file << j;

	//std::cout << j.dump(2);

	printf("\nfiles saved ^^^:\n");

}

void TileMap::loadMap(std::string path, std::unordered_map<std::string, std::vector<sf::Texture>>& assets)
{


	ongridTileMap.clear();
	std::fstream File;
	File.open(path, std::ios::in);
	nlohmann::json Doc = nlohmann::json::parse(File) ;

	//std::vector<Tile> temp_offgridTilemap;
	//std::unordered_map<std::string, Tile> temp_ongridTileMap;

	File.close();
	ongridTileMap = Doc["tilemap"];
	tileSize = Doc["tile_size"];
	offgridTilemap = Doc["offgrid"];
	//std::cout << Doc.dump(2);


	for (auto& pair : ongridTileMap) {
		pair.second.setTexture(assets[pair.second.type][pair.second.variant]);
		pair.second.gridpos = getStringtoVector2i(pair.first); // assign grid pos to tile
		pair.second.pos = pair.second.pos * tileSize; // assign window pixel position
		pair.second.setPosition(pair.second.pos);
		pair.second.setScale(2, 2);
	}

	for (auto& tile : offgridTilemap) {
		tile.setTexture(assets[tile.type][tile.variant]);
		tile.pos = tile.pos;
		tile.setPosition(tile.pos);
		tile.setScale(2, 2);
	}

}

void TileMap::draw(sf::RenderWindow& window, sf::Vector2f offset)
{

	// offgrif tiles
	for (auto& tile : offgridTilemap) {
		tile.pos -= offset;
		tile.setPosition(tile.pos);
		window.draw(tile);

	}

	// ongrid tiles
	for (auto& pair : ongridTileMap) {

		pair.second.pos -= offset; // move tilemap camera
		pair.second.setPosition(pair.second.pos);
		window.draw(pair.second);

		//std::cout << pair.first << '\n';
	}

}


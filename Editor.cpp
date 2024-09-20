#include "Editor.h"
#include "utils.h"

Editor::Editor()
{

	window.create(sf::VideoMode(960, 736), "platformer dafluffypotato");
	window.setFramerateLimit(60);

	event = sf::Event();

	assets = {
		{ "grass"       ,      load_images("tiles/grass/")},
		{ "stone"       ,      load_images("tiles/stone/")},
		{ "decor"       ,      load_images("tiles/decor/")},
		{ "large_decor" ,      load_images("tiles/large_decor/")},
		{ "spawners"    ,      load_images("tiles/spawners/")},
	};

	vecTile_list.clear();
	
	for (auto& str : assets) {
		vecTile_list.push_back(str.first);
	}

	// declarations
	this->tile_group = 0;
	this->tile_variant = 0;

	// gives size of a vector of assets textures 
	float varintssize = assets[vecTile_list[tile_group]].size(); // (here to copy only)
	
	// gives number of tile_types
	float tilegroupSize = vecTile_list.size(); // (here to copy only)

	tilemap = TileMap();
	tilemap.setMap(assets);


}

void Editor::drawGrid(sf::Vector2f offset, int tileSize)
{
	
	int linesNumx = window.getSize().x / tileSize + 2;
	for (int i = -2; i < linesNumx; i++) { // x-axis
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(i * 32 , -100)),
			sf::Vertex(sf::Vector2f(i * 32 , 800 ))
		};

		window.draw(line, 2, sf::Lines);
	}

	int linesNumy = window.getSize().y / tileSize + 2;
	for (int i = -2; i < linesNumy; i++) { // x-axis
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(-100 , i * 32 )),
			sf::Vertex(sf::Vector2f(1000 , i * 32 ))
		};

		window.draw(line, 2, sf::Lines);
	}
	
}

void Editor::run()
{
	while (window.isOpen())
	{
		// delta time
		float deltaTime = this->clock.restart().asSeconds();

		// time timers declared
		this->CameraLeftMovementTimer   += deltaTime;
		this->CameraRightMovementTimer  += deltaTime;
		this->CameraUpMovementTimer     += deltaTime;
		this->CameraDownMovementTimer   += deltaTime;



		sf::Vector2f fscroll = { float(int(scroll.x)) , float(int(scroll.y)) }; //  scroll per frame (float)
		scroll = { 0,0 };

		sf::Vector2f mpos = { float(sf::Mouse::getPosition(window).x) , float(sf::Mouse::getPosition(window).y) }; // mouse position per frame

		sf::Vector2i cursorWindowPos = { int(mpos.x / tilemap.tileSize), int(mpos.y / tilemap.tileSize) }; // mouse grid pos

		// to solve truncate toward 0 problem
		sf::Vector2f antiTrucnategridPos = {(mpos.x + gridoffset.x) / tilemap.tileSize , (mpos.y + gridoffset.y) / tilemap.tileSize}; 
		if ((mpos.x + gridoffset.x) / tilemap.tileSize < 0)		antiTrucnategridPos.x--;
		if ((mpos.y + gridoffset.y) / tilemap.tileSize < 0)		antiTrucnategridPos.y--;
		
		sf::Vector2i mouseGridLoc = { int(antiTrucnategridPos.x) , int(antiTrucnategridPos.y) }; // mouse grid pos

		// total map screen offset
		gridoffset += fscroll;


		//window.clear(sf::Color(70, 170, 220)); // sky-blue background
		//window.clear(sf::Color(30, 30, 30)); // grey background
		window.clear(); // black background

		sf::Texture* texture; // texture for currently displayed sprite
		texture = &this->assets[vecTile_list[this->tile_group]][this->tile_variant];

		sf::Sprite current_tile_img(*texture); // currently selected tile sprite
		current_tile_img.setPosition(30, 30); // displayed on top-right
		current_tile_img.setScale(3, 3);
		current_tile_img.setColor(sf::Color(255, 255, 255, 150)); // trasnparent



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    window.close();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (CameraLeftMovementTimer > 0.1) {
				scroll.x = -32; // to move camera
				CameraLeftMovementTimer = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (CameraRightMovementTimer > 0.1) {
				scroll.x = 32; // to move camera
				CameraRightMovementTimer = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (CameraUpMovementTimer > 0.1) {
				scroll.y = -32; // to move camera
				CameraUpMovementTimer = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (CameraDownMovementTimer > 0.1) {
				scroll.y = 32; // to move camera
				CameraDownMovementTimer = 0;
			}
		}
		

		// place tiles with mouse left click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // when left mouse button is pressed

			sf::Vector2i tile_ongrid_pos = mouseGridLoc; // mouse grid position is store in new sf::Vector2f
			std::string grid_loc = std::to_string(int(tile_ongrid_pos.x)) + ';' + std::to_string(int(tile_ongrid_pos.y)); // get string pos on grid

			// make a Tile
			Tile tile( sf::Vector2f(cursorWindowPos.x , cursorWindowPos.y) , vecTile_list[tile_group], tile_variant);  // tile window position
			tile.setTexture(this->assets[vecTile_list[tile_group]][this->tile_variant]);  // set its texture
			tilemap.ongridTileMap.insert(std::make_pair(grid_loc, tile)); // insert tile in ongrid map

			std::cout << grid_loc << '\n';

		}

		// delete tiles with mouse right click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

			std::string mloc = std::to_string(mouseGridLoc.x) + ';' + std::to_string(mouseGridLoc.y); // gets grid position to delete tiles
			tilemap.ongridTileMap.erase(mloc);
		}

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			// MOUSE INPUT EVENTS

			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == sf::Mouse::Left) {

				}
				if (event.mouseButton.button == sf::Mouse::Right) {
				
				}
				if (event.mouseButton.button == sf::Mouse::Middle) {
					//printf("mouse middle\n");
				}
				
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					//printf("released left\n");
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					//printf("released right\n");
				}
				if (event.mouseButton.button == sf::Mouse::Middle) {
					//printf("released middle\n");
				}
			}
			
			
			if (event.type == sf::Event::MouseWheelScrolled) {
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

					// with shift key and mouse scroll change TILE_GROUP 
					if (event.mouseWheelScroll.delta > 0) {
						this->tile_group = int(this->tile_group + event.mouseWheelScroll.delta) % vecTile_list.size();
						this->tile_variant = 0;
					}
					if (event.mouseWheelScroll.delta < 0) {
						this->tile_group = int(this->tile_group + event.mouseWheelScroll.delta) % vecTile_list.size();
						this->tile_variant = 0;
					}

				}
				else {
					// not shift key, change TILE_VARIANT with mouse scroll
					if (event.mouseWheelScroll.delta > 0) {
						this->tile_variant = int(this->tile_variant + event.mouseWheelScroll.delta) % assets[vecTile_list[tile_group]].size();
						//this->tile_variant %=  
					}
					if (event.mouseWheelScroll.delta < 0) {
						this->tile_variant = int(this->tile_variant + event.mouseWheelScroll.delta) % assets[vecTile_list[tile_group]].size();
						//this->tile_variant %=  
					}

				}

			}


			// KEYBOARD INPUT EVENTS

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					//std::cout << "left\n";
					movement[0] = true;
					//scroll.x = -32;
				}
				if (event.key.code == sf::Keyboard::Right) {
					//std::cout << "Right\n";
					movement[1] = true;
					//scroll.x = 32;
				}
				if (event.key.code == sf::Keyboard::Up) {
					//std::cout << "Up\n";
					//movement[2] = true;
					//scroll.y = -32;
				}
				if (event.key.code == sf::Keyboard::Down) {
					//std::cout << "Down\n";
					//movement[3] = true;
					//scroll.y = 32;
				}
				if (event.key.code == sf::Keyboard::S) {
					//tilemap.saveMap("map0.json");
					tilemap.saveMap("data/maps/0.json");
				}
				if (event.key.code == sf::Keyboard::L) {
					//tilemap.loadMap("map0.json", assets);
					tilemap.loadMap("data/maps/0.json", assets);
					//tilemap.loadMap("data/maps/2.json", assets);
				}
				if (event.key.code == sf::Keyboard::LControl) {

				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Left) {
					//std::cout << "left\n";
					movement[0] = false;
					scroll.x = 0;
				}
				if (event.key.code == sf::Keyboard::Right) {
					//std::cout << "Right\n";
					movement[1] = false;
					scroll.x = 0;
				}
				if (event.key.code == sf::Keyboard::Up) {
					//std::cout << "Up\n";
					//movement[2] = false;
					scroll.y = 0;
				}
				if (event.key.code == sf::Keyboard::Down) {
					//std::cout << "Down\n";
					//movement[3] = false;
					scroll.y = 0;
				}
			}


			//end event loop
		}



		tilemap.draw(window, fscroll);

		window.draw(current_tile_img); // this draws image of selected texture on top_left 

		// to draw the same sprite by changing its pos , to avoid creating new sprite object
		current_tile_img.setPosition(cursorWindowPos.x * tilemap.tileSize , cursorWindowPos.y * tilemap.tileSize); // selected texture shadow on cursor
		current_tile_img.setScale(2,2);

		window.draw(current_tile_img); // // this draws image of selected texture on cursor



		this->drawGrid(gridoffset, 32);
		

		window.display();
	}

}

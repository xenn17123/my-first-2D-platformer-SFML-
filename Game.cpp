#include "Game.h"
#include "utils.h"
#include "Collisions.h"

// TODO:- 


Game::Game()
{
    window.create(sf::VideoMode(960, 720), "platformer dafluffypotato");
	window.setFramerateLimit(60);
	setWindowPtr(window);
	
	
	event = sf::Event();
	assets = {
		{ "grass"       , load_images("tiles/grass/")},
		{ "stone"       , load_images("tiles/stone/")},
		{ "decor"       , load_images("tiles/decor/")},
		{ "large_decor" , load_images("tiles/large_decor/")}, // 0 = stone, 1 = grass, 2 = tree
		{ "spawners"    , load_images("tiles/spawners/")},    // 0 = player, 1 = enemy
		{ "player"      , load_images("entities/")},
		{ "clouds"      , load_images("clouds/")},
		{ "images"      , load_images("")},   // 0 = background, 1 = gun, 2 = projectile
	};
	
	anim_assets = {
		// player
		{ "player/idle"        ,  Animation(load_images("entities/player/idle/"), 8, true)},
		{ "player/run"         ,  Animation(load_images("entities/player/run/"), 5, true)},
		{ "player/jump"        ,  Animation(load_images("entities/player/jump/"), 5, true)},
		{ "player/slide"       ,  Animation(load_images("entities/player/slide/"), 5, true)},
		{ "player/wall_slide"  ,  Animation(load_images("entities/player/wall_slide/"), 5, true)},

		//enemy
		{ "enemy/idle"         ,  Animation(load_images("entities/enemy/idle/"), 8, true)},
		{ "enemy/run"          ,  Animation(load_images("entities/enemy/run/"), 5, true)},
		
		// particles
		{ "particles/leaf"     ,  Animation(load_images("particles/leaf/"), 20, false)},
		{ "particles/particle" ,  Animation(load_images("particles/particle/"), 6, false)},
	};

	particlesMap = {
		{"leaf"     ,  vecParticlesLeaf       },
		{"particle" ,  vecParticlesparticle   },
	};
	
	background = sf::Sprite(assets["images"][0]);
	background.setScale(3, 3);


	tilemap = TileMap();

	tilemap.loadMap("data/maps/1.json", assets);
	//tilemap.loadMap("map0.json", assets);
	//tilemap.loadMap("data/maps/0.json", assets);

	for (auto& tile : tilemap.extract("large_decor", 2, true)) {
		leaf_spawners.push_back(sf::FloatRect(tile.getPosition() + sf::Vector2f(5, 5), sf::Vector2f(50, 30)));
	}

	// spawning player on map
	for (auto& tile : tilemap.extract("spawners", 0, false)) {
		vecPlayers.push_back(Player(anim_assets, tile.getPosition(), { 14, 18 }));
		//vecPlayers.push_back(Player(anim_assets, tile.getPosition()));
		vecPlayers[0].getAccessToParticlesVector(particlesMap);
		vecPlayers[0].poolParticles();
	}

	// spawning enemies on map
	for (auto& tile : tilemap.extract("spawners", 1, false)) {
		Enemy enemy(anim_assets, tile.getPosition(), { 14, 18 });
		enemy.setGun(assets["images"][1], assets["images"][2]);
		vecEnemies.push_back(enemy);
	}

	clouds = Clouds(assets, 30);

	
}

void Game::run()
{
	while(window.isOpen())
	{
		window.clear(sf::Color(70, 170, 220));

		window.draw(background);


		scroll += ((vecPlayers[0].pos + vecPlayers[0].size / 2) - (sf::Vector2f(window.getSize().x, window.getSize().y) / 2) - scroll) / 1.f;
		sf::Vector2f fscroll = { float(int(scroll.x)) , float(int(scroll.y)) };

		this->gridoffset += fscroll; // total offset since start of game
		tilemap.gridOffset = this->gridoffset;
		

		// leaf particles spawns from trees
		for (auto& rect : leaf_spawners) {
			rect.left -= fscroll.x;
			rect.top  -= fscroll.y;
			if (rand() * 5 < rect.width * rect.height) {
				sf::Vector2f pos_temp(rect.left + randrangefloat(0, 1) * rect.width, rect.top + randrangefloat(0, 1) * rect.height );
				sf::Vector2f vel_temp(-0.15, 0.4);
				this->particlesMap["leaf"].push_back(Particles("leaf", pos_temp, vel_temp, randrangeint(0, 17), anim_assets));
				//std::cout << "particle spanwd now \n";
			}

			//draws leaf spawners rects on trees
			//sf::RectangleShape re;
			//re.setPosition(rect.left, rect.top);
			//re.setSize(sf::Vector2f(50, 30));
			//re.setOutlineThickness(1);
			//window.draw(re);
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			window.close();
		}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	player.velocity.y = -4;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	player.velocity.y = 4;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if(event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Left) {
					//std::cout << "left\n";
					movement[0] = true;
				}
				if (event.key.code == sf::Keyboard::Right) {
					//std::cout << "Right\n";
					movement[1] = true;
				}
				if (event.key.code == sf::Keyboard::Up) {
					//std::cout << "Up\n";
					//player.jump();
					vecPlayers[0].jump();
				}
				if (event.key.code == sf::Keyboard::Down) {
					//std::cout << "Down\n";
				}
				if (event.key.code == sf::Keyboard::Space) {
					//std::cout << "Space\n";
					//player.velocity.y = -10;
					vecPlayers[0].velocity.y = -10;
				}
				if (event.key.code == sf::Keyboard::X) {
					//std::cout << "X\n";
					//player.dash();
					vecPlayers[0].dash();
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Left) {
					//std::cout << "left\n";
					movement[0] = false;
				}
				if (event.key.code == sf::Keyboard::Right) {
					//std::cout << "Right\n";
					movement[1] = false;
				}
				if (event.key.code == sf::Keyboard::Up) {
					//std::cout << "Up\n";
					//player.velocity.y = 0;
				}
				if (event.key.code == sf::Keyboard::Down) {
					//std::cout << "Down\n";
					//player.velocity.y = 0;
				}
			}



			//end event loop
		}

		

		imgPos.x = (movement[1] - movement[0]) * 4;
		
		
		clouds.update();
		
		clouds.draw(window, fscroll);
		tilemap.draw(window, fscroll);
		
		
		// player Enemy collision checks
		for (auto& enemy : vecEnemies) {
			if (abs(vecPlayers[0].dashing) >= 50) { // if player is in middle of dash 
				if (checkCollision_Player_Enemy(vecPlayers[0], enemy)) { // if player and enemy are colliding
					enemy.damaged(1);
				}
			}
		}

		// players functionalities
		for (auto& player : vecPlayers) {
			player.draw(window, fscroll);
			player.update(tilemap, imgPos);
			getTilesAround(tilemap, player);
		}

		// enemies functionalities 
		for (auto& enemy : vecEnemies) {
			enemy.draw(window , fscroll);
			enemy.update(tilemap, sf::Vector2f(0, 0));
			for (auto& bulletIter : enemy.bulletsArray) {
				if (checkCollision_Bullet_Player(bulletIter, vecPlayers[0])) { // player and bullet check collision test
					collisionResponse_Bullet_Player(bulletIter, vecPlayers[0]);
				}
			}
		}


		// update and draw particles/leaf objects
		for (int i = 0; i < particlesMap["leaf"].size()  ; i++) {
			particlesMap["leaf"][i].update();
			particlesMap["leaf"][i].draw(window, fscroll);
			
			particlesMap["leaf"][i].pos.x += sin(particlesMap["leaf"][i].animation.frame * 0.03) * 0.3; // wavy effect on x-axis
			
			if (particlesMap["leaf"][i].kill) {
				particlesMap["leaf"].erase(particlesMap["leaf"].begin() + i);
				i--;
			}
		}

		for (int i = 0; i < particlesMap["particle"].size(); i++) {
			particlesMap["particle"][i].update();
			particlesMap["particle"][i].draw(window, fscroll);

			if (particlesMap["particle"][i].kill) {
				particlesMap["particle"][i].isVisible = false;
			}
		}


		window.display();
		std::cout << getMainBuffer();
		getMainBuffer().clear();
	}
}

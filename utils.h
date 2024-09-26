#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include <filesystem>
#include "TileMap.h"
#include "PhysicsEntity.h"



// load textures
sf::Texture load_image(std::string path);

std::vector<sf::Texture> load_images(std::string path);

void setWindowPtr(sf::RenderWindow& windowptr);

sf::RenderWindow* getWindowPtr();

sf::Vector2f screenShake(sf::Vector2f offset , float shakeRoughness);

// random numbers
int randrangeint(int min, int max);

float randrangefloat(float min, float max);

// returns grid position in "x ; y" format without any modifications
std::string getgridposString(int x, int y);

// returns grid position in "x ; y" format without any modifications
std::string getgridposString(sf::Vector2i pos);

// takes gridpos string of format "x ; y" and return sf::Vector2i(x , y) from it without any modifications
sf::Vector2i getStringtoVector2i(std::string pos);

// takes sf::Vector2f(world position) and returns grid position by dividing it by tileSize,
// adjusted to solve the truncate problem when nums are negative
sf::Vector2i getGridposCalculated(sf::Vector2f worldPos);


// return array of tile grid positions around the entity 
sf::Vector2i* getTilesAround(TileMap& tilemap, PhysicsEntity& entity);


// log buffer that stores all log messages
std::string& getMainBuffer();

 // append std::string to the main log buffer
void appendToBuffer(std::string str);


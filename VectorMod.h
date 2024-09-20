#pragma once
class VectorMod
{
};

#include<SFML\System\Vector2.hpp>
#include<cmath>

// Overloads to support basic operations between 2 vectorf
sf::Vector2f operator+(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f operator-(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f operator*(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f operator/(const sf::Vector2f& left, const sf::Vector2f& right);

// Overloads to support operations with float 
sf::Vector2f operator+(const sf::Vector2f& left, float right);

sf::Vector2f operator-(const sf::Vector2f& left, float right);

sf::Vector2f operator*(const sf::Vector2f& left, float right);

sf::Vector2f operator/(const sf::Vector2f& left, float right);

// Overloads to support operations with float on the left side
sf::Vector2f operator+(float left, const sf::Vector2f& right);

sf::Vector2f operator-(float left, const sf::Vector2f& right);

sf::Vector2f operator*(float left, const sf::Vector2f& right);

sf::Vector2f operator/(float left, const sf::Vector2f& right);

// normalize a vector
sf::Vector2f normalize(sf::Vector2f& other);


// Overloads to support basic operations between 2 vectori
sf::Vector2i operator+(const sf::Vector2i& left, const sf::Vector2i& right);

sf::Vector2i operator-(const sf::Vector2i& left, const sf::Vector2i& right);
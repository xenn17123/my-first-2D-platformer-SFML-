#include "VectorMod.h"


sf::Vector2f operator+(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x + right.x, left.y + right.y);
}

sf::Vector2f operator-(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x - right.x, left.y - right.y);
}

sf::Vector2f operator*(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x * right.x, left.y * right.y);
}

sf::Vector2f operator/(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x / right.x, left.y / right.y);
}

sf::Vector2f operator+(const sf::Vector2f& left, float right)
{
    return sf::Vector2f(left.x + right, left.y + right);
}

sf::Vector2f operator-(const sf::Vector2f& left, float right)
{
    return sf::Vector2f(left.x - right, left.y - right);
}

sf::Vector2f operator*(const sf::Vector2f& left, float right)
{
    return sf::Vector2f(left.x * right, left.y * right);
}

sf::Vector2f operator/(const sf::Vector2f& left, float right)
{
    return sf::Vector2f(left.x / right, left.y / right);
}

// Overloads to support operations with float on the left side
sf::Vector2f operator+(float left, const sf::Vector2f& right)
{
    return sf::Vector2f(left + right.x, left + right.y);
}

sf::Vector2f operator-(float left, const sf::Vector2f& right)
{
    return sf::Vector2f(left - right.x, left - right.y);
}

sf::Vector2f operator*(float left, const sf::Vector2f& right)
{
    return sf::Vector2f(left * right.x, left * right.y);
}

sf::Vector2f operator/(float left, const sf::Vector2f& right)
{
    return sf::Vector2f(left / right.x, left / right.y);
}

// normalize a vector
sf::Vector2f normalize(sf::Vector2f& other)
{
    float length = std::sqrt(other.x * other.x + other.y * other.y);
    if (length != 0)     (other = sf::Vector2f(other.x / length, other.y / length));
    return other;
}

sf::Vector2i operator+(const sf::Vector2i& left, const sf::Vector2i& right)
{
    return sf::Vector2i(left.x + right.x, left.y + right.y);
}

sf::Vector2i operator-(const sf::Vector2i& left, const sf::Vector2i& right)
{
    return sf::Vector2i(left.x - right.x, left.y - right.y);
}
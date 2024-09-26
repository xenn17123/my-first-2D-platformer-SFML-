#pragma once
#include <SFML/Graphics.hpp>
#include "VectorMod.h"


class Button : public sf::Drawable
{
private:
    // Method to draw the button
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

    enum states{
        normal = 0,
        hovered,
        clicked
    };

public:
    // Button attributes
    sf::Color default_color = sf::Color(250, 50, 50, 200);  // Default color
    int width = 100;  // Width of the button
    int height = 60;  // Height of the button
    sf::Vector2f button_position = { 0.f, 0.f };  // Position of the button
    sf::Font font;
    sf::Text text;

    // Constructor to initialize button with specific attributes
    Button(float posX, float posY, int w, int h, sf::Color color);

    // Default constructor
    Button();

    // Method to set position
    void setPosition(float x, float y);

    void setTextPosition();
};

#include "Button.h"


// Method to draw the button
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    // Create a VertexArray to represent the button's two triangles (6 vertices total)
    sf::VertexArray triangles(sf::Triangles, 6);

    // Define the four corners of the rectangle
    sf::Vector2f topLeft = sf::Vector2f(button_position.x, button_position.y);
    sf::Vector2f topRight = sf::Vector2f(button_position.x + width, button_position.y);
    sf::Vector2f bottomLeft = sf::Vector2f(button_position.x, button_position.y + height);
    sf::Vector2f bottomRight = sf::Vector2f(button_position.x + width, button_position.y + height);

    // First triangle (top-left, top-right, bottom-right)
    triangles[0].position = topLeft;
    triangles[1].position = topRight;
    triangles[2].position = bottomRight;

    // Second triangle (top-left, bottom-right, bottom-left)
    triangles[3].position = topLeft + 0;
    triangles[4].position = bottomRight + 0;
    triangles[5].position = bottomLeft + 0;

    // Set the color for each vertex
    for (int i = 0; i < 6; ++i) {
        triangles[i].color = default_color;
    }

    // Draw the triangles (button) on the target
    target.draw(triangles, states);
    target.draw(this->text);
}


// Constructor to initialize button
Button::Button(float posX, float posY, int w, int h, sf::Color color)
    : button_position(posX, posY), width(w), height(h), default_color(color)
{
    this->font.loadFromFile("data/fonts/codec/Codec-Warm-Regular-trial.ttf");
    // select the font
    text.setFont(font); // font is a sf::Font
    text.setString("Hello world");
    text.setCharacterSize(10); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(this->button_position);
}

Button::Button()
{
    this->font.loadFromFile("data/fonts/codec/Codec-Warm-Regular-trial.ttf");
    // select the font
    text.setFont(font); // font is a sf::Font
    text.setString("Hello world");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

// Method to set the button's position
void Button::setPosition(float x, float y) 
{
    this->button_position = sf::Vector2f(x, y);
    text.setPosition(this->button_position);

}

void Button::setTextPosition()
{

}


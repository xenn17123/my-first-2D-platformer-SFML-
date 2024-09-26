#pragma once
#include "Button.h"

class StartMenu
{
private:

	Button startGame;

public:

	void setComponents();

	void draw(sf::RenderWindow& window);
};


#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Board.h"

class Interface
{
public:
	Interface();
	~Interface();

	void run();

private:
	sf::RenderWindow win;

	bool _paused{ false };
	Board _board;
};


#pragma once

#include <iostream>
#include "Constants.h"

class StateField
{
public:
	StateField();
	~StateField();

	void update();
	std::uint8_t* getField();
	int getGeneration() { return _generation; }
	void setPoint(const sf::Vector2i&);

private:
	int _generation;
	std::uint8_t *_curr, *_next;

	int determineState(int _x);
};


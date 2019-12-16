/*
Transformations:
Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These rules, which compare the behavior of the automaton to real life, can be condensed into the following:
Any live cell with two or three neighbors survives.
Any dead cell with three live neighbors becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.
*/

#include "StateField.h"
#include <utility>

#include "dbg.h"

StateField::StateField()
{
	_generation = 1;

	_curr = new std::uint8_t[TOTSIZE]{};
	_next = new std::uint8_t[TOTSIZE]{};

	// text values:
	_curr[1650] = 1;_curr[1651] = 1; _curr[1652] = 1; 
	_curr[2451] = 1; _curr[2452] = 1; _curr[2453] = 1; 
	_curr[3252] = 1; _curr[3253] = 1; _curr[3254] = 1;
	_curr[4052] = 1; _curr[4053] = 1; _curr[4054] = 1;
	_curr[4852] = 1; _curr[4853] = 1; _curr[4854] = 1;
}

StateField::~StateField()
{
	delete[] _curr, _next;
}

std::uint8_t* StateField::getField()
{
	return _curr;
}

void StateField::setPoint(const sf::Vector2i& pos)
{
	int i = (pos.y * SCREEN_W) + pos.x;
	_curr[i] = 1;
}

void StateField::update()
{
	for (auto i = 0; i < TOTSIZE; i++)
	{
		_next[i] = determineState(i);
	}

	std::swap<std::uint8_t*>(_curr, _next);
	_generation++;
}

int StateField::determineState(int _x)
{
	int p{}, q{}, a{}, b{}, r{};

	// top corner case
	if (_x >= SCREEN_W) 
	{
		b = _x - SCREEN_W;
	}
	else
	{
		b = TOTSIZE - SCREEN_W + _x;
	}

	// bottom corner case
	if (_x >= (TOTSIZE - SCREEN_W))
	{
		a = (_x + SCREEN_W) - TOTSIZE;
	}
	else
	{
		a = _x + SCREEN_W;
	}

	if (_curr[_x - 1] == 1) r++;
	if (_curr[_x + 1] == 1) r++;
	if (_curr[b - 1] == 1) r++;
	if (_curr[b] == 1) r++;
	if (_curr[b + 1] == 1) r++;
	if (_curr[a - 1] == 1) r++;
	if (_curr[a] == 1) r++;
	if (_curr[a + 1] == 1) r++;

	if(_curr[_x] == 1 and (r == 2 or r==3 ))
		return 1;
	if(_curr[_x] == 0 and r == 3)
		return 1;

	return 0;
};
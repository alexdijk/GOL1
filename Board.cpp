#include <utility>

#include "Board.h"
#include "Constants.h"
// #include "dbg.h"

Board::Board()
{
	try
	{
		_texture.create(SCREEN_W, SCREEN_H);
		_sprite.setTexture(_texture);
		_sprite.setOrigin(sf::Vector2f(0.f, 0.f));
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Board::~Board()
{
}

void Board::update(bool paused)
{
	std::uint8_t* _t = new uint8_t[TOTSIZE * 4]{};
	unsigned int pos{},
		black = sf::Color::Black.toInteger(), 
		white = sf::Color::White.toInteger();

	if(not paused)
		_state.update();

	std::uint8_t* _f = _state.getField();

	for (int i{}; i < TOTSIZE; i++)
	{
		if (_f[i] == 0)
		{
			_t[4 * pos] = (white >> 16) & 0xFF;
			_t[4 * pos + 1] = (white >> 8) & 0xFF;
			_t[4 * pos + 2] = white & 0xFF;
			_t[4 * pos + 3] = 0xFF;
			++pos;
		}
		else
		{
			_t[4 * pos] = (black >> 16) & 0xFF;
			_t[4 * pos + 1] = (black >> 8) & 0xFF;
			_t[4 * pos + 2] = black & 0xFF;
			_t[4 * pos + 3] = 0xFF;
			++pos;
		}
	}

	_texture.update(_t);
	_statustext.setText(_state.getGeneration());
	delete[] _t;
}

void Board::draw(sf::RenderWindow& ren)
{
	ren.draw(_sprite);
	ren.draw(_statustext.getTextObj());
}

void Board::handleEvents(sf::Event& ev)
{
}

void Board::handleMouseEvent(const sf::Vector2i& pos)
{
	_state.setPoint(pos);
}
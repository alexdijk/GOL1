#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "StateField.h"
#include "StatusText.h"

class Board
{
public:
	Board();
	~Board();

	void update(bool);
	void draw(sf::RenderWindow&);
	void handleEvents(sf::Event&);
	void handleMouseEvent(const sf::Vector2i&);

private:
	StateField _state{};
	StatusText _statustext{};

	sf::Texture _texture{};
	sf::Sprite _sprite{};
};
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class StatusText
{
public:
	StatusText();
	~StatusText() {}

	void setText(std::string);
	void setText(int);

	sf::Text& getTextObj();

private:
	std::string	_str{};
	sf::Font _font{};
	sf::Text _text{};
};


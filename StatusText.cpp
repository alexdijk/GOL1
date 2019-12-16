
#include "StatusText.h"

StatusText::StatusText()
{

	if (not _font.loadFromFile("./arial.ttf"))
		throw("Could not load font");

	_text.setFont(_font);
	_text.setCharacterSize(24);
	_text.setFillColor(sf::Color::Red);
	_text.setPosition(sf::Vector2f(650.f, 570.f));

}

void StatusText::setText(std::string s)
{
	_str = s;
	_text.setString("Gen:" + _str);
}

void StatusText::setText(int i)
{
	_str = std::to_string(i);
	_text.setString("Gen:" + _str);
}

sf::Text& StatusText::getTextObj()
{
	return _text;
}
#include "Interface.h"
#include <iostream>

#include <sstream>
// #include "dbg.h"

Interface::Interface()
{
	std::cout << "hello cruel world\n";
try{
	win.create(sf::VideoMode(SCREEN_W, SCREEN_H), "Conway\'s Life");
}catch(std::exception& e)
{
	std::cerr << e.what() << std::endl;
}

	if (not win.isOpen())
		throw "Cannot open RenderWindow";
}

Interface::~Interface()
{
}

void Interface::run()
{
	while (win.isOpen())
	{
		sf::Event ev;

		while (win.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::MouseButtonPressed:

				switch (ev.mouseButton.button)
				{
				case sf::Mouse::Left:
					_paused = true;
					break;
				case sf::Mouse::Right:
					// I want a magnifier
					break;
				default:
					break;
				}
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseButtonReleased:

				switch (ev.mouseButton.button)
				{
				case sf::Mouse::Left:
					_paused = false;
					break;
				case sf::Mouse::Right:
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		if (_paused)
		{
			sf::Vector2i vec = sf::Mouse::getPosition(win);
			_board.handleMouseEvent(vec);

			//std::stringstream ss{};
			//ss << vec.x << " - " << vec.y;
			//dbg(ss.str());
		}
			
		_board.update(_paused);
	
		win.clear(sf::Color::White);
		_board.draw(win);
		win.display();
	}
}

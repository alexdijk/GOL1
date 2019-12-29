#include "Interface.h"
#include <iostream>

#include <sstream>
#include "imgui.h"
#include "imgui-SFML.h"

// #include "dbg.h"

Interface::Interface()
{
	std::cout << "hello cruel world\n";

	try{
		win.create(sf::VideoMode(SCREEN_W, SCREEN_H), "Conway\'s Life");
	
		if (not win.isOpen())
			throw "Cannot open RenderWindow";

		ImGui::SFML::Init(win);
	} 
	catch(std::exception& e)
	{	
		std::cerr << e.what() << std::endl;
	}
}

Interface::~Interface()
{
}

void Interface::run()
{
	sf::Clock deltaTime;

	while (win.isOpen())
	{
		sf::Event ev;

		while (win.pollEvent(ev))
		{
			ImGui::SFML::ProcessEvent(ev);

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
	
		ImGui::SFML::Update(win, deltaTime.restart());

		ImGui::Begin("Main tools");
		ImGui::Button("button");
		ImGui::End();

		win.clear(sf::Color::White);
		_board.draw(win);
		ImGui::SFML::Render(win);
		win.display();
	}

	ImGui::SFML::Shutdown();
}


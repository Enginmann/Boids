#include "Simulation.h"



Simulation::Simulation()
{
	initialize();
}

void Simulation::initialize()
{
	windowSize = sf::Vector2u(800, 800);
	window.create(sf::VideoMode(windowSize), "Boids", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	renderer.initialize(&window);
}

void Simulation::run()
{
	while (window.isOpen())
	{
		checkEvents();

		renderer.run();
	}
}

void Simulation::checkEvents()
{
	while (const auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			close();
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				close();
			}
		}
	}
}

void Simulation::close()
{
	window.close();
}

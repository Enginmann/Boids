#include "Simulation.h"



Simulation::Simulation() : renderer(BOIDS_COUNT), engine(BOIDS_COUNT)
{
	initialize();
}

void Simulation::initialize()
{
	windowSize = sf::Vector2u(1200, 800);
	window.create(sf::VideoMode(windowSize), "Boids", sf::Style::Titlebar | sf::Style::Close);

	renderer.initialize(&window);

	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		positions[i][0] = 0;
		positions[i][1] = 0;
		velocities[i][0] = 0;
		velocities[i][1] = 0;
	}
}

void Simulation::run()
{
	while (window.isOpen())
	{
		checkEvents();

		renderer.run(positions);
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

#include "Simulation.h"
#include <chrono>
#include <random>



Simulation::Simulation() : renderer(BOIDS_COUNT), engine(BOIDS_COUNT, dt)
{
	initialize();
}

void Simulation::initialize()
{
	windowSize = sf::Vector2u(1200, 800);
	window.create(sf::VideoMode(windowSize), "Boids", sf::Style::Titlebar | sf::Style::Close);

	renderer.initialize(&window);

	initializeBoids();
}

void Simulation::initializeBoids()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> randX(0, windowSize.x);
	std::uniform_real_distribution<float> randY(0, windowSize.y);
	std::uniform_real_distribution<float> randVel(-0.00000002, 0.000000002);

	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		positions[i][0] = randX(gen);
		positions[i][1] = randY(gen);
		velocities[i][0] = randVel(gen);
		velocities[i][1] = randVel(gen);
	}
}

void Simulation::run()
{
	using Clock = std::chrono::steady_clock;
	Clock::time_point lastTime = Clock::now();
	double accumulator = 0;


	while (window.isOpen())
	{
		checkEvents();


		auto currentTime = Clock::now();
		std::chrono::duration<double> elapsed = currentTime - lastTime;
		double frameTime = elapsed.count();
		lastTime = currentTime;

		if (frameTime > 0.25)
			frameTime = 0.25;

		accumulator += frameTime;

		while (accumulator >= dt)
		{
			engine.run(positions, velocities, windowSize);
			accumulator -= dt;
		}


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

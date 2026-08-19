#include "Simulation.h"
#include <chrono>
#include <random>



Simulation::Simulation()
{
	initialize();
}

void Simulation::initialize()
{
	windowSize = sf::VideoMode::getDesktopMode().size;
	windowSize.x -= 10;
	windowSize.y -= 120;
	window.create(sf::VideoMode(windowSize), "Boids", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition({0, 0});

	renderer.initialize(&window);

	perceptionRadius = 140;

	initializeBoids();
}

void Simulation::initializeBoids()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> randX(0, windowSize.x);
	std::uniform_real_distribution<float> randY(0, windowSize.y);
	std::uniform_real_distribution<float> randVel(-600, 600);

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
			engine.run(positions, velocities, windowSize, BOIDS_COUNT, dt, perceptionRadius);
			accumulator -= dt;
		}


		renderer.run(positions, velocities, BOIDS_COUNT, perceptionRadius);
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
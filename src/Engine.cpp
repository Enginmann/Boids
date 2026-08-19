#include "Engine.h"



Engine::Engine(const int boidsCount, const int deltaTime) : BOIDS_COUNT(boidsCount), dt(deltaTime)
{

}

void Engine::run(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize)
{
	moveBoids(positions, velocities, windowSize);
}

void Engine::moveBoids(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize)
{
	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		positions[i][0] += velocities[i][0] * dt;
		positions[i][1] += velocities[i][1] * dt;

		// wrapping around the screen
		if (positions[i][0] > windowSize.x)
			positions[i][0] = 0;
		else if (positions[i][0] < 0)
			positions[i][0] = windowSize.x;

		if (positions[i][1] > windowSize.y)
			positions[i][1] = 0;
		else if (positions[i][1] < 0)
			positions[i][1] = windowSize.y;
	}
}

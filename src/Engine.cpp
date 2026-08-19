#include "Engine.h"
#include <vector>
#include <cmath>

Engine::Engine()
{
}

void Engine::run(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt, const float perceptionRadius)
{
	alignBoids(positions, velocities, BOIDS_COUNT, dt, perceptionRadius);

	moveBoids(positions, velocities, windowSize, BOIDS_COUNT, dt);
}

void Engine::moveBoids(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt)
{
	float maxSpeed = 500;
	float minSpeed = 200;

	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		velocities[i][0] += accelarations[i][0] * dt;
		velocities[i][1] += accelarations[i][1] * dt;

		float speed = std::sqrt(velocities[i][0] * velocities[i][0] + velocities[i][1] * velocities[i][1]);

		if (speed > maxSpeed)
		{
			velocities[i][0] = (velocities[i][0] / speed) * maxSpeed;
			velocities[i][1] = (velocities[i][1] / speed) * maxSpeed;
		}
		else if (speed < minSpeed && speed > 0)
		{
			velocities[i][0] = (velocities[i][0] / speed) * minSpeed;
			velocities[i][1] = (velocities[i][1] / speed) * minSpeed;
		}

		positions[i][0] += velocities[i][0] * dt;
		positions[i][1] += velocities[i][1] * dt;

		// wrapping around the screen
		if (positions[i][0] > windowSize.x+50)
			positions[i][0] = 0;
		else if (positions[i][0]+50 < 0)
			positions[i][0] = windowSize.x;

		if (positions[i][1] > windowSize.y+50)
			positions[i][1] = 0;
		else if (positions[i][1]+50 < 0)
			positions[i][1] = windowSize.y;
	}
}

void Engine::alignBoids(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const double dt, const float perceptionRadius)
{	
	float alignmentFactor = 1;

	accelarations = std::vector<std::vector<float>>(BOIDS_COUNT, std::vector<float>(2, 0));


	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		accelarations[i][0] = 0;
		accelarations[i][1] = 0;

		int neighbors = 0;
		float avgVelX = 0;
		float avgVelY = 0;

		for (int j = 0; j < BOIDS_COUNT; j++)
		{
			if (j == i)
				continue;

			float dx = positions[i][0] - positions[j][0];
			float dy = positions[i][1] - positions[j][1];

			if (dx*dx + dy*dy <= perceptionRadius*perceptionRadius)
			{
				neighbors++;

				avgVelX += velocities[j][0];
				avgVelY += velocities[j][1];
			}
		}

		if (neighbors > 0)
		{
			avgVelX /= neighbors;
			avgVelY /= neighbors;

			accelarations[i][0] = (avgVelX - velocities[i][0]) * alignmentFactor;
			accelarations[i][1] = (avgVelY - velocities[i][1]) * alignmentFactor;
		}
	}
}
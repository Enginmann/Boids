#include "Engine.h"
#include <vector>
#include <cmath>

Engine::Engine()
{
	alignmentFactor = 0.9;
	cohesionFactor = 4;
	separationFactor = 15;
}

void Engine::run(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt, const float perceptionRadius)
{
	accelarations = std::vector<std::vector<float>>(BOIDS_COUNT, std::vector<float>(2, 0));

	alignment(positions, velocities, BOIDS_COUNT, perceptionRadius);

	cohesion(positions, velocities, BOIDS_COUNT, perceptionRadius);

	separation(positions, velocities, BOIDS_COUNT, perceptionRadius);

	moveBoids(positions, velocities, windowSize, BOIDS_COUNT, dt);
}

void Engine::moveBoids(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt)
{
	float maxSpeed = 650;
	float minSpeed = 350;

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

void Engine::alignment(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius)
{
	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		int neighbors = 0;
		float avgVelX = 0;
		float avgVelY = 0;

		for (int j = 0; j < BOIDS_COUNT; j++)
		{
			if (j == i)
				continue;

			float dx = positions[i][0] - positions[j][0];
			float dy = positions[i][1] - positions[j][1];

			if (dx * dx + dy * dy <= perceptionRadius * perceptionRadius)
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

			accelarations[i][0] += (avgVelX - velocities[i][0]) * alignmentFactor;
			accelarations[i][1] += (avgVelY - velocities[i][1]) * alignmentFactor;
		}
	}
}

void Engine::cohesion(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius)
{
	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		int neighbors = 0;
		float avgPosX = 0;
		float avgPosY = 0;

		for (int j = 0; j < BOIDS_COUNT; j++)
		{
			if (j == i)
				continue;

			float dx = positions[i][0] - positions[j][0];
			float dy = positions[i][1] - positions[j][1];

			if (dx * dx + dy * dy <= perceptionRadius * perceptionRadius)
			{
				neighbors++;

				avgPosX += positions[j][0];
				avgPosY += positions[j][1];
			}
		}

		if (neighbors > 0)
		{
			avgPosX /= neighbors;
			avgPosY /= neighbors;

			accelarations[i][0] += (avgPosX - positions[i][0]) * cohesionFactor;
			accelarations[i][1] += (avgPosY - positions[i][1]) * cohesionFactor;
		}
	}
}

void Engine::separation(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius)
{
	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		for (int j = 0; j < BOIDS_COUNT; j++)
		{
			if (j == i)
				continue;

			float dx = positions[i][0] - positions[j][0];
			float dy = positions[i][1] - positions[j][1];

			if (dx*dx + dy*dy <= perceptionRadius*perceptionRadius)
			{
				accelarations[i][0] -= (positions[j][0] - positions[i][0]) / std::sqrt(dx*dx + dy*dy) * separationFactor;
				accelarations[i][1] -= (positions[j][1] - positions[i][1]) / std::sqrt(dx*dx + dy*dy) * separationFactor;
			}
		}
	}
}
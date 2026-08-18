#include "Engine.h"



Engine::Engine(const int boidsCount, const int deltaTime) : BOIDS_COUNT(boidsCount), dt(deltaTime)
{

}

void Engine::run(float positions[][2], float velocities[][2])
{
	moveBoids(positions, velocities);
}

void Engine::moveBoids(float positions[][2], float velocities[][2])
{
	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		positions[i][0] += velocities[i][0] * dt;
		positions[i][1] += velocities[i][1] * dt;
	}
}

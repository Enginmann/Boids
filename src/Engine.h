#pragma once
#include "SFML/Graphics.hpp"


class Engine
{
private:
	std::vector<std::vector<float>> accelarations;

public:
	Engine();

	void run(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt, const float perceptionRadius);

private:
	void moveBoids(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt);

	void alignment(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius);

	void cohesion(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius);
};
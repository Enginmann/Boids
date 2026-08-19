#pragma once
#include "SFML/Graphics.hpp"


class Engine
{
private:
	std::vector<std::vector<float>> accelarations;

public:
	Engine();

	void run(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt);

private:
	void moveBoids(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize, const int BOIDS_COUNT, const double dt);

	void alignBoids(float positions[][2], float velocities[][2], const int BOIDS_COUNT, const double dt);
};
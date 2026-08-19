#pragma once
#include "SFML/Graphics.hpp"


class Engine
{
private:
	const int BOIDS_COUNT;
	const int dt;

public:
	Engine(const int boidsCount, const int deltaTime);

	void run(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize);

private:
	void moveBoids(float positions[][2], float velocities[][2], const sf::Vector2u &windowSize);
};
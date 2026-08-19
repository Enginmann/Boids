#pragma once

#include "SFML/Graphics.hpp"



class Renderer
{
private:
	sf::RenderWindow* window;

public:
	Renderer();

	void initialize(sf::RenderWindow* window);

	void run(const float positions[][2], const float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius);

private:
	void drawBoids(const float positions[][2], const float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius);
};
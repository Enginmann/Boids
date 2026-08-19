#pragma once

#include "SFML/Graphics.hpp"



class Renderer
{
private:
	sf::RenderWindow* window;

	const int BOIDS_COUNT;

public:
	Renderer(const int boidsCount);

	void initialize(sf::RenderWindow* window);

	void run(const float positions[][2]);

private:
	void drawBoids(const float positions[][2]);
};
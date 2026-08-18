#pragma once

#include "Engine.h"
#include "Renderer.h"



class Simulation
{
private:
	Renderer renderer;
	Engine engine;

	sf::RenderWindow window;
	sf::Vector2u windowSize;

	static const int BOIDS_COUNT = 100;

	float positions[BOIDS_COUNT][2];
	float velocities[BOIDS_COUNT][2];

public:
	Simulation();

	void run();

private:
	void initialize();

	void checkEvents();

	void close();
};
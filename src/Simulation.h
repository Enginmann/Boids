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

	static const int BOIDS_COUNT = 150;
	const float dt = 1/60.0; // 60 Hz

	float positions[BOIDS_COUNT][2];
	float velocities[BOIDS_COUNT][2];

	float perceptionRadius;

public:
	Simulation();

	void run();

private:
	void initialize();

	void initializeBoids();

	void checkEvents();

	void close();
};
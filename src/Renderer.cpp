#include "Renderer.h"



Renderer::Renderer()
{
}

void Renderer::initialize(sf::RenderWindow * window)
{
	this->window = window;
}

void Renderer::run(const float positons[][2], const int BOIDS_COUNT)
{
	window->clear();

	drawBoids(positons, BOIDS_COUNT);

	window->display();
}

void Renderer::drawBoids(const float positions[][2], const int BOIDS_COUNT)
{
	sf::CircleShape boid(9);
	boid.setFillColor(sf::Color::White);

	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		boid.setPosition({positions[i][0], positions[i][1]});
		window->draw(boid);
	}
}

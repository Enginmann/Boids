#include "Renderer.h"



Renderer::Renderer(const int boidsCount) : BOIDS_COUNT(boidsCount)
{
}

void Renderer::initialize(sf::RenderWindow * window)
{
	this->window = window;
}

void Renderer::run(const float positons[][2])
{
	window->clear();

	drawBoids(positons);

	window->display();
}

void Renderer::drawBoids(const float positions[][2])
{
	sf::CircleShape boid(9);
	boid.setFillColor(sf::Color::White);

	for (int i = 0; i < 100; i++)
	{
		boid.setPosition({positions[i][0], positions[i][1]});
		window->draw(boid);
	}
}

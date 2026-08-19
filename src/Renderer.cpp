#include "Renderer.h"
#include <cmath>


Renderer::Renderer()
{
}

void Renderer::initialize(sf::RenderWindow * window)
{
	this->window = window;
}

void Renderer::run(const float positons[][2], const float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius)
{
	window->clear();

	drawBoids(positons, velocities, BOIDS_COUNT, perceptionRadius);

	window->display();
}

void Renderer::drawBoids(const float positions[][2], const float velocities[][2], const int BOIDS_COUNT, const float perceptionRadius)
{
	sf::ConvexShape boid;
	boid.setPointCount(3);
	boid.setFillColor(sf::Color::White);

	boid.setPoint(0, sf::Vector2f(10, 0));
	boid.setPoint(1, sf::Vector2f(-10, -8));
	boid.setPoint(2, sf::Vector2f(-10, 8));

	for (int i = 0; i < BOIDS_COUNT; i++)
	{
		float angle = std::atan2(velocities[i][1], velocities[i][0]);
		boid.setRotation(sf::radians(angle));
		boid.setPosition({positions[i][0], positions[i][1]});

		if (i == BOIDS_COUNT - 1)
		{
			boid.setFillColor(sf::Color::Red);
			sf::CircleShape perception(perceptionRadius);
			perception.setOrigin({perceptionRadius, perceptionRadius});
			perception.setPosition({positions[i][0], positions[i][1]});
			perception.setFillColor(sf::Color::Transparent);
			perception.setOutlineColor(sf::Color::Red);
			perception.setOutlineThickness(5);
			window->draw(perception);
		}

		window->draw(boid);
	}
}

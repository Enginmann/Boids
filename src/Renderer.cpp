#include "Renderer.h"



Renderer::Renderer()
{
}

void Renderer::initialize(sf::RenderWindow * window)
{
	this->window = window;
}

void Renderer::run()
{
	window->clear();

	window->display();
}
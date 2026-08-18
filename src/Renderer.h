#pragma once

#include <SFML/Graphics.hpp>



class Renderer
{
private:
	sf::RenderWindow* window;

public:
	Renderer();

	void initialize(sf::RenderWindow* window);

	void run();

private:

};
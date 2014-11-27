#pragma once

#include <SFML\Graphics.hpp>

class Application
{
public:
	Application();
	~Application();

	void init(int width, int height, const std::string& title);
	void shutdown();

	void run();

protected:
	void processEvent();
	void tick();
	void render();
	sf::RenderWindow* _window;

};


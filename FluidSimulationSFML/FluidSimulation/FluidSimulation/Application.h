#pragma once

#include <SFML\Graphics.hpp>
#include "Skeleton.h"
#include "ParticleSystem.h"

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
	void handleKeyEvents(sf::Event& evt);
	void handleMouseEvents(sf::Event& evt);
	
	void clearSkeletons();
	
	sf::RenderWindow* _window;


	std::vector<Skeleton*> _skeletons;
	ParticleSystem _particleSystem;

	bool _mouseDown;
};


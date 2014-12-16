#pragma once

#include <SFML\Graphics.hpp>
#include "FrameClock.h"
#include "ClockHUD.h"

#define GRAVITY 4.82f

class Skeleton;

class Application
{
public:
	Application();
	~Application();

	void init(int width, int height, const std::string& title);
	void shutdown();

	void run();
	void addSkeleton(Skeleton* skeleton);

protected:
	void processEvent();
	void tick();
	void render();
	void handleKeyEvents(sf::Event& evt);
	void handleMouseEvents(sf::Event& evt);
	
	void createNewSkeleton();
	void resetApplication();
	void clearSkeletons();
	
	sf::RenderWindow* _window;

	
	std::vector<Skeleton*> _skeletons;
	sfx::FrameClock _frameClock;
	sf::Text _skeletonText;
	sf::Font _font;
	ClockHUD _clockHUD;

	bool _mouseDown;
	
};


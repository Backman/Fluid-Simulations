#include "Application.h"
#include "Skeleton.h"
#include <iostream>
#include <sstream>

Application::Application() :
	_window(nullptr), _mouseDown(false),
	_clockHUD(_frameClock, _font)
{
	_frameClock.setSampleDepth(100);
	if (!_font.loadFromFile("Data/verdana.ttf"))
	{
		sf::err() << "Failed to load verdana.ttf";
		exit(EXIT_FAILURE);
	}
	_skeletonText.setFont(_font);

	createNewSkeleton();
}


Application::~Application()
{
	clearSkeletons();
}

void Application::clearSkeletons() {
	while (!_skeletons.empty()) {
		delete _skeletons.back();
		_skeletons.pop_back();
	}
}

void Application::resetApplication() {
	clearSkeletons();
	createNewSkeleton();
}

void Application::addSkeleton(Skeleton* skeleton) {
	_skeletons.push_back(skeleton);
}

void Application::createNewSkeleton() {
	Skeleton* skeleton = new Skeleton(GRAVITY);
	Skeleton::initHumanSkeleton(skeleton, true);
	addSkeleton(skeleton);
}

void Application::shutdown() {
	if (_window != nullptr) {
		delete _window;
		_window = nullptr;
	}
}

void Application::init(int width, int height, const std::string& title) {
	if (_window == nullptr) {
		_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

		sf::Vector2f textPos(_window->getSize().x - 100, 10.0f);
		_skeletonText.setPosition(textPos);
	}
}


void Application::run() {
	if (_window == nullptr) {
		return;
	}

	while (_window->isOpen()) {
		_frameClock.beginFrame();

		processEvent();
		tick();
		render();

		_frameClock.endFrame();
	}
}

void Application::processEvent() {
	sf::Event evt;
	while (_window->pollEvent(evt)) {
		if (evt.type == sf::Event::Closed) {
			_window->close();
		}
		handleKeyEvents(evt);
		handleMouseEvents(evt);
	}
}

void Application::tick() {
	for (auto& skeleton : _skeletons) {
		skeleton->update(1.0f / 60.0f);
	}
}

void Application::handleKeyEvents(sf::Event& evt) {
	switch (evt.key.code) {
	case sf::Keyboard::Escape:
		_window->close();
		break;
	}
	
	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == sf::Keyboard::R) {
			resetApplication();
		}
		if (evt.key.code == sf::Keyboard::Space) {
			createNewSkeleton();
		}
	}
}

void Application::handleMouseEvents(sf::Event& evt) {
	if (evt.type == sf::Event::MouseButtonPressed) {
		if (evt.mouseButton.button == sf::Mouse::Left) {
			_mouseDown = true;
		}
	}
	if (evt.type == sf::Event::MouseButtonReleased) {
		if (evt.mouseButton.button == sf::Mouse::Left) {
			_mouseDown = false;
			_skeletons[0]->releaseMouse();
		}
	}
	if (_mouseDown) {
		sf::Vector2f mousePos(sf::Mouse::getPosition(*_window));
		_skeletons[0]->addMouseForce(mousePos);
	}
}

void Application::render() {
	_window->clear();

	for (auto& skeleton : _skeletons) {
		skeleton->render(_window);
	}

	int skeletonSize = _skeletons.size();
	std::ostringstream convert;
	convert << skeletonSize;
	_skeletonText.setString(convert.str());
	_window->draw(_skeletonText);
	
	_window->draw(_clockHUD);

	_window->display();
}


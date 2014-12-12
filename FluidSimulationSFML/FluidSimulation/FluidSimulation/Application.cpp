#include "Application.h"
#include <iostream>

Application::Application() :
	_window(nullptr), _mouseDown(false)
{
	_skeletons.push_back(new Skeleton(1.0f));
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

void Application::shutdown() {
	if (_window != nullptr) {
		delete _window;
		_window = nullptr;
	}
}

void Application::init(int width, int height, const std::string& title) {
	if (_window == nullptr) {
		_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	}
}


void Application::run() {
	if (_window == nullptr) {
		return;
	}

	while (_window->isOpen()) {
		processEvent();
		tick();
		render();
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
	//_particleSystem.timeStep();
	for (auto& skeleton : _skeletons) {
		skeleton->update(1.0f / 60.0f);
	}
}

void Application::handleKeyEvents(sf::Event& evt) {
	switch (evt.key.code) {
	case sf::Keyboard::Space:
		//_particleSystem.timeStep();
		break;

	case sf::Keyboard::Escape:
		_window->close();
		break;
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

	_window->display();
}


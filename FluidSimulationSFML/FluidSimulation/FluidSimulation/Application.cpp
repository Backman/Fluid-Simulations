#include "Application.h"


Application::Application() :
	_window(nullptr)
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
	}
}

void Application::tick() {
	//_particleSystem.timeStep();
	for (auto& skeleton : _skeletons) {
		skeleton->update(1.0f / 600.0f);
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

void Application::render() {
	_window->clear();

	//_particleSystem.render(_window);

	for (auto& skeleton : _skeletons) {
		skeleton->render(_window);
	}

	_window->display();
}


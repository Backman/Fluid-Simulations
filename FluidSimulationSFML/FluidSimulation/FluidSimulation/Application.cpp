#include "Application.h"


Application::Application() :
	_window(nullptr)
{
}


Application::~Application()
{
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
	}
}

void Application::tick() {

}

void Application::render() {
	_window->clear();

	_window->display();
}


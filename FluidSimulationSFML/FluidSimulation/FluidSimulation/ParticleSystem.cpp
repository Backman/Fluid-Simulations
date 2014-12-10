#include "ParticleSystem.h"
#include "Constraint.h"

ParticleSystem::ParticleSystem() :
	_timeStep(1.0f / 60.0f), _gravity(0.0f, 1.0f)
{
	_points[0].setPosition(sf::Vector2f(500.0f, 0.0f), true);
	_points[0].setMass(10.0f);

	_points[1].setPosition(sf::Vector2f(100.0f, 100.0f), true);
	_points[1].setMass(10.0f);

}


ParticleSystem::~ParticleSystem()
{
}


void ParticleSystem::timeStep() {
	accumulateForces();
	verlet();
	applyConstraints(3);
}

void ParticleSystem::verlet() {
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		sf::Vector2f& x = _points[i].getPosition();
		sf::Vector2f temp = x;
		sf::Vector2f& oldX = _points[i].getOldPosition();
		sf::Vector2f& a = _points[i].getForce();

		x = x * 2.0f - oldX + a * _timeStep * _timeStep;

		oldX = temp;
	}
}

void ParticleSystem::accumulateForces() {
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		_points[i].clearForce();
		_points[i].addForce(_gravity);
	}
}

void ParticleSystem::applyConstraints(int iterations) {

	for (int j = 0; j < iterations; ++j) {
		for (int i = 0; i < _constraints.size(); ++i) {
			_constraints[i]->applyConstraint();
		}

		_points[0].setPosition(sf::Vector2f(500.0f, 0.0f));
	}
}

void ParticleSystem::render(sf::RenderWindow* rw) {
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		sf::CircleShape s(5.0);
		s.setPosition(_points[i].getPosition());
		s.setFillColor(sf::Color::Red);

		rw->draw(s);
	}
}
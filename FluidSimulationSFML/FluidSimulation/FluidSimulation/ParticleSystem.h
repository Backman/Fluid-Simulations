#pragma once

#include <SFML\Graphics.hpp>
#include "PointMass.h"

#define NUM_PARTICLES 2
#define NUM_CONSTRAINTS 1

class Constraint;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void timeStep();
	void render(sf::RenderWindow* rw);

private:
	void verlet();
	void accumulateForces();
	void applyConstraints(int iterations);

	PointMass _points[NUM_PARTICLES];

	std::vector<Constraint*> _constraints;

	sf::Vector2f _gravity;
	float _timeStep;
};


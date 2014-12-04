#pragma once

#include "Constraint.h"
#include "PointMass.h"

class Skeleton
{
public:
	Skeleton(float gravity);
	~Skeleton();

	void update(float timeStep);
	void render(sf::RenderWindow* rw);

private:
	void clearConstraints();
	void clearPoints();

	void verlet(float timeStep);
	void accumulateForces();
	void applyConstraints(int iterations);

	void initHumanSkeleton();

	std::vector<PointMass*> _points;
	std::vector<Constraint*> _constraints;
	float _gravity;
};


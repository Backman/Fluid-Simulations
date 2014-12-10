#include "Skeleton.h"


Skeleton::Skeleton(float gravity) : 
	_gravity(gravity)
{
	initHumanSkeleton();
}


Skeleton::~Skeleton()
{
	clearConstraints();
	clearPoints();
}

void Skeleton::clearConstraints() {
	while (!_constraints.empty()) {
		delete _constraints.back();
		_constraints.pop_back();
	}
}

void Skeleton::clearPoints() {
	while (!_points.empty()) {
		delete _points.back();
		_points.pop_back();
	}
}

void Skeleton::update(float timeStep) {
	accumulateForces();
	verlet(timeStep);
	applyConstraints(3);
}

void Skeleton::verlet(float timeStep) {
	for (auto& p : _points) {
		sf::Vector2f& x = p->getPosition();
		sf::Vector2f temp = x;
		sf::Vector2f& oldX = p->getOldPosition();
		sf::Vector2f& a = p->getForce();

		x = x * 2.0f - oldX + a * timeStep * timeStep;
		oldX = temp;
	}
}

void Skeleton::accumulateForces() {
	for (auto& p : _points) {
		p->clearForce();
		p->addForce(sf::Vector2f(0.0f, _gravity));
	}
}

void Skeleton::applyConstraints(int iterations) {
	for (int i = 0; i < iterations; ++i) {
		for (auto& c : _constraints) {
			c->applyConstraint();
		}
	}
}

void Skeleton::initHumanSkeleton() {
	clearConstraints();
	clearPoints();

	float neckLength = 40.0f;
	_points.push_back(new PointMass(320.0f, 180.0f, 20.0f));
	_points.push_back(new PointMass(320.0f, 180.0f + neckLength, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[0], _points[1]));

	float shoulderWidth = 40.0f;
	float shoulderYPos = neckLength + 20.0f;
	_points.push_back(new PointMass(320 - shoulderWidth, 180.0f + shoulderYPos, 20.0f));
	_points.push_back(new PointMass(320 + shoulderWidth, 180.0f + shoulderYPos, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[1], _points[2]));
	_constraints.push_back(new LinearConstraint(_points[1], _points[3]));

	float ribbcageSize = shoulderYPos + 70.0f;
	_points.push_back(new PointMass(320, ribbcageSize + 180.0f, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[1], _points[4]));
	_constraints.push_back(new LinearConstraint(_points[2], _points[4]));
	_constraints.push_back(new LinearConstraint(_points[3], _points[4]));

	float upperArmLen = shoulderYPos + 80.0f;
	_points.push_back(new PointMass(320.0f - shoulderWidth, 180.0f + upperArmLen, 20.0f));
	_points.push_back(new PointMass(320.0f + shoulderWidth, 180.0f + upperArmLen, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[2], _points[5]));
	_constraints.push_back(new LinearConstraint(_points[3], _points[6]));

	float lowerArmLen = upperArmLen + 80.0f;
	_points.push_back(new PointMass(320.0f - shoulderWidth, 180.0f + lowerArmLen, 20.0f));
	_points.push_back(new PointMass(320.0f + shoulderWidth, 180.0f + lowerArmLen, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[5], _points[7]));
	_constraints.push_back(new LinearConstraint(_points[6], _points[8]));

	float lowerBack = ribbcageSize + 1.0f;
	_points.push_back(new PointMass(320.0f, 180.0f + lowerBack, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[4], _points[9]));

	float upperLegs = lowerBack + 30.0f;
	float legSeparation = 30.0f;
	_points.push_back(new PointMass(320.0f - legSeparation, 180.0f + upperLegs, 20.0f));
	_points.push_back(new PointMass(320.0f + legSeparation, 180.0f + upperLegs, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[9], _points[10]));
	_constraints.push_back(new LinearConstraint(_points[9], _points[11]));
	_constraints.push_back(new LinearConstraint(_points[10], _points[11]));

	float knee = upperLegs + 80.0f;
	_points.push_back(new PointMass(320.0f - legSeparation, 180.0f + knee, 20.0f));
	_points.push_back(new PointMass(320.0f + legSeparation, 180.0f + knee, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[10], _points[12]));
	_constraints.push_back(new LinearConstraint(_points[11], _points[13]));

	float lowerLegs = knee + 80.0f;
	_points.push_back(new PointMass(320.0f - legSeparation, 180.0f + lowerLegs, 20.0f));
	_points.push_back(new PointMass(320.0f + legSeparation, 180.0f + lowerLegs, 20.0f));
	_constraints.push_back(new LinearConstraint(_points[12], _points[14]));
	_constraints.push_back(new LinearConstraint(_points[13], _points[15]));

	for (auto& p : _points) {
		p->setOldPosition(p->getPosition());
		_constraints.push_back(new NotUnderScreenConstraint(p));
	}
}

void Skeleton::render(sf::RenderWindow* rw) {

	for (auto& constraint : _constraints) {
		constraint->render(rw);
	}

	for (auto& point : _points) {
		float radius = 5.0f;
		sf::CircleShape c(radius);
		c.setPosition(point->getPosition());
		c.setFillColor(sf::Color::Red);
		c.setOrigin(radius, radius);
		rw->draw(c);
	}
}


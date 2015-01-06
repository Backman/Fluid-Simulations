#include "Skeleton.h"
#include "Constraint.h"
#include "PointMass.h"
#include <iostream>

float randomRange(float min, float max) {
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

Skeleton::Skeleton(float gravity) : 
	_gravity(gravity), _mouseDown(false)
{
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

void Skeleton::addPointMass(PointMass* pointMass) {
	_points.push_back(pointMass);
}

void Skeleton::addConstraint(Constraint* constraint) {
	_constraints.push_back(constraint);
}

void Skeleton::update(float timeStep) {
	accumulateForces();
	verlet(timeStep);
	applyConstraints(1);
}

void Skeleton::verlet(float timeStep) {
	for (auto& p : _points) {
		sf::Vector2f& x = p->getPosition();
		sf::Vector2f temp = x;
		sf::Vector2f& oldX = p->getOldPosition();
		sf::Vector2f& a = p->getForce() * p->getInvMass();

		x = x * 2.0f - oldX + a * timeStep * timeStep;
		oldX = temp;
	}
}

void Skeleton::accumulateForces() {
	for (auto& p : _points) {
		p->clearForce();
		p->addForce(sf::Vector2f(0.0f, _gravity * p->getMass()));
	}

	while (!_forceQueue.empty()) {
		ForceApplier applier = _forceQueue.front();
		_forceQueue.pop();

		applier.point->addForce(applier.force);
	}
}

void Skeleton::applyConstraints(int iterations) {
	for (int i = 0; i < iterations; ++i) {
		for (auto& c : _constraints) {
			c->applyConstraint();
		}
	}
}

void Skeleton::releaseMouse() {
	_mouseDown = false;
}

void Skeleton::addMouseForce(const sf::Vector2f& mousePos) {

	if (!_mouseDown) {
		float minLen = std::numeric_limits<float>::max();
		for (auto& point : _points) {
			float len = distanceBetween(point->getPosition(), mousePos);

			if (len < minLen) {
				minLen = len;
				_nearestPoint = point;
			}
		}
		_mouseDown = true;
	}

	sf::Vector2f force = mousePos - _nearestPoint->getPosition();
	addForce(force * 10.0f, _nearestPoint);
}

void Skeleton::addForce(const sf::Vector2f& force, PointMass* point) {
	ForceApplier forceApplier;
	forceApplier.force = force;
	forceApplier.point = point;
	_forceQueue.push(forceApplier);
}

#pragma region Init Skeleton Functions

void Skeleton::initHumanSkeleton(Skeleton* skeleton, bool randomPos) {
	skeleton->clearConstraints();
	skeleton->clearPoints();

	float startX = 320.0f;
	float startY = 180.0f;

	if (randomPos) {
		startX = randomRange(50.0f, 800.0f);
		startY = randomRange(10.0f, 400.0f);
	}

	float neckLength = 40.0f;
	skeleton->addPointMass(new PointMass(startX, startY, 20.0f));									// 0
	skeleton->addPointMass(new PointMass(startX, startY + neckLength, 20.0f));						// 1
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[0], skeleton->_points[1]));

	float shoulderWidth = 40.0f;
	float shoulderYPos = neckLength + 20.0f;
	skeleton->addPointMass(new PointMass(startX - shoulderWidth, startY + shoulderYPos, 20.0f));	// 2
	skeleton->addPointMass(new PointMass(startX + shoulderWidth, startY + shoulderYPos, 20.0f));	// 3
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[1], skeleton->_points[2]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[1], skeleton->_points[3]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[2], skeleton->_points[3]));

	float ribbcageYPos = shoulderYPos + 80.0f;
	float ribbcageSize = 30.0f;
	skeleton->addPointMass(new PointMass(startX - ribbcageSize, ribbcageYPos + startY, 20.0f));		// 4
	skeleton->addPointMass(new PointMass(startX + ribbcageSize, ribbcageYPos + startY, 20.0f));		// 5
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[4], skeleton->_points[5]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[1], skeleton->_points[4]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[2], skeleton->_points[4]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[3], skeleton->_points[4]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[1], skeleton->_points[5]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[2], skeleton->_points[5]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[3], skeleton->_points[5]));

	float upperArmLen = shoulderYPos + 60.0f;
	skeleton->addPointMass(new PointMass(startX - shoulderWidth, startY + upperArmLen, 20.0f));		// 6
	skeleton->addPointMass(new PointMass(startX + shoulderWidth, startY + upperArmLen, 20.0f));		// 7
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[2], skeleton->_points[6]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[3], skeleton->_points[7]));

	float lowerArmLen = upperArmLen + 80.0f;
	skeleton->addPointMass(new PointMass(startX - shoulderWidth, startY + lowerArmLen, 20.0f));		// 8
	skeleton->addPointMass(new PointMass(startX + shoulderWidth, startY + lowerArmLen, 20.0f));		// 9
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[6], skeleton->_points[8]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[7], skeleton->_points[9]));

	//float lowerBack = ribbcageSize + 1.0f;
	//skeleton->addPointMass(new PointMass(startX, startY + lowerBack, 20.0f));						// 10
	//skeleton->addConstraint(new LinearConstraint(skeleton->_points[4], skeleton->_points[9]));

	float upperLegs = ribbcageYPos + 30.0f;
	float legSeparation = ribbcageSize + 5.0f;
	skeleton->addPointMass(new PointMass(startX - legSeparation, startY + upperLegs, 20.0f));		// 10
	skeleton->addPointMass(new PointMass(startX + legSeparation, startY + upperLegs, 20.0f));		// 11
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[4], skeleton->_points[10]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[4], skeleton->_points[11]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[5], skeleton->_points[10]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[5], skeleton->_points[11]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[10], skeleton->_points[11]));

	float knee = upperLegs + 80.0f;
	skeleton->addPointMass(new PointMass(startX - legSeparation, startY + knee, 20.0f));			// 12
	skeleton->addPointMass(new PointMass(startX + legSeparation, startY + knee, 20.0f));			// 13
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[10], skeleton->_points[12]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[11], skeleton->_points[13]));

	float lowerLegs = knee + 80.0f;
	skeleton->addPointMass(new PointMass(startX - legSeparation, startY + lowerLegs, 20.0f));		// 14
	skeleton->addPointMass(new PointMass(startX + legSeparation, startY + lowerLegs, 20.0f));		// 15
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[12], skeleton->_points[14]));
	skeleton->addConstraint(new LinearConstraint(skeleton->_points[13], skeleton->_points[15]));


	// Angular constraints
	// Head
	skeleton->addAngularConstraint(skeleton->_points[0], skeleton->_points[2], 30.0f);
	skeleton->addAngularConstraint(skeleton->_points[0], skeleton->_points[3], 30.0f);
	// Left shoulder
	skeleton->addAngularConstraint(skeleton->_points[1], skeleton->_points[6], 50.0f);
	// Right shoulder
	skeleton->addAngularConstraint(skeleton->_points[1], skeleton->_points[7], 50.0f);
	// Left elbow
	skeleton->addAngularConstraint(skeleton->_points[2], skeleton->_points[8], 60.0f);
	// Right elbow
	skeleton->addAngularConstraint(skeleton->_points[3], skeleton->_points[9], 60.0f);
	//// Rib cage 
	//skeleton->addConstraint(new AngularConstraint(skeleton->_points[2], skeleton->_points[10], distanceBetween(skeleton->_points[2]->getPosition(), skeleton->_points[10]->getPosition()) - 20.0f));
	//skeleton->addConstraint(new AngularConstraint(skeleton->_points[3], skeleton->_points[11], distanceBetween(skeleton->_points[3]->getPosition(), skeleton->_points[11]->getPosition()) - 20.0f));
	//// Middle back
	////skeleton->addConstraint(new AngularConstraint(skeleton->_points[4], skeleton->_points[10], 20.0f));
	////skeleton->addConstraint(new AngularConstraint(skeleton->_points[4], skeleton->_points[11], 20.0f));
	//// Pelvis
	////skeleton->addConstraint(new AngularConstraint(skeleton->_points[3], skeleton->_points[12], 80.0f));
	//// Left leg
	skeleton->addAngularConstraint(skeleton->_points[12], skeleton->_points[2], 60.0f);
	//// Right leg
	skeleton->addAngularConstraint(skeleton->_points[13], skeleton->_points[3], 60.0f);
	//// Left knee
	skeleton->addAngularConstraint(skeleton->_points[14], skeleton->_points[10], 60.0f);
	//skeleton->addConstraint(new AngularConstraint(skeleton->_points[15], skeleton->_points[11], 80.0f));
	//// Right knee
	skeleton->addAngularConstraint(skeleton->_points[15], skeleton->_points[11], 60.0f);
	//skeleton->addConstraint(new AngularConstraint(skeleton->_points[14], skeleton->_points[10], 80.0f));
	//// Dont cross knees
	skeleton->addAngularConstraint(skeleton->_points[12], skeleton->_points[13], 30.0f);



	for (auto& p : skeleton->_points) {
		p->setOldPosition(p->getPosition());
		skeleton->addConstraint(new MinMaxConstraint(p, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024.0f, 768.0f)));
	}
}
#pragma endregion

void Skeleton::addAngularConstraint(PointMass* p1, PointMass* p2, float dist) {
	addConstraint(new AngularConstraint(p1, p2, distanceBetween(p1->getPosition(), p2->getPosition()) - dist));
}

void Skeleton::render(sf::RenderWindow* rw) {

	for (auto& constraint : _constraints) {
		constraint->render(rw);
	}

	for (auto& point : _points) {
		point->render(rw);
	}
}


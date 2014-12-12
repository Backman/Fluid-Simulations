#include "Skeleton.h"


Skeleton::Skeleton(float gravity) : 
	_gravity(gravity), _mouseDown(false)
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

	while (!_forceQueue.empty()) {
		ForceApplier applier = _forceQueue.front();
		_forceQueue.pop();

		//applier.point->addForce(normalize(applier.force) * 300.0f);
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
	addForce(force, _nearestPoint);
}

void Skeleton::addForce(const sf::Vector2f& force, PointMass* point) {
	ForceApplier forceApplier;
	forceApplier.force = force;
	forceApplier.point = point;
	_forceQueue.push(forceApplier);
}

#pragma region Init Skeleton Functions

void Skeleton::initHumanSkeleton() {
	clearConstraints();
	clearPoints();

	float neckLength = 40.0f;
	_points.push_back(new PointMass(320.0f, 180.0f, 20.0f));								// 0
	_points.push_back(new PointMass(320.0f, 180.0f + neckLength, 20.0f));					// 1
	_constraints.push_back(new LinearConstraint(_points[0], _points[1]));

	float shoulderWidth = 40.0f;
	float shoulderYPos = neckLength + 20.0f;
	_points.push_back(new PointMass(320 - shoulderWidth, 180.0f + shoulderYPos, 20.0f));	// 2
	_points.push_back(new PointMass(320 + shoulderWidth, 180.0f + shoulderYPos, 20.0f));	// 3
	_constraints.push_back(new LinearConstraint(_points[1], _points[2]));
	_constraints.push_back(new LinearConstraint(_points[1], _points[3]));

	float ribbcageSize = shoulderYPos + 60.0f;
	_points.push_back(new PointMass(320, ribbcageSize + 180.0f, 20.0f));					// 4
	_constraints.push_back(new LinearConstraint(_points[1], _points[4]));
	_constraints.push_back(new LinearConstraint(_points[2], _points[4]));
	_constraints.push_back(new LinearConstraint(_points[3], _points[4]));

	float upperArmLen = shoulderYPos + 80.0f;
	_points.push_back(new PointMass(320.0f - shoulderWidth, 180.0f + upperArmLen, 20.0f));	// 5
	_points.push_back(new PointMass(320.0f + shoulderWidth, 180.0f + upperArmLen, 20.0f));	// 6
	_constraints.push_back(new LinearConstraint(_points[2], _points[5]));
	_constraints.push_back(new LinearConstraint(_points[3], _points[6]));

	float lowerArmLen = upperArmLen + 80.0f;
	_points.push_back(new PointMass(320.0f - shoulderWidth, 180.0f + lowerArmLen, 20.0f));	// 7
	_points.push_back(new PointMass(320.0f + shoulderWidth, 180.0f + lowerArmLen, 20.0f));	// 8
	_constraints.push_back(new LinearConstraint(_points[5], _points[7]));
	_constraints.push_back(new LinearConstraint(_points[6], _points[8]));

	float lowerBack = ribbcageSize + 1.0f;
	_points.push_back(new PointMass(320.0f, 180.0f + lowerBack, 20.0f));					// 9
	_constraints.push_back(new LinearConstraint(_points[4], _points[9]));

	float upperLegs = lowerBack + 30.0f;
	float legSeparation = 30.0f;
	_points.push_back(new PointMass(320.0f - legSeparation, 180.0f + upperLegs, 20.0f));	// 10
	_points.push_back(new PointMass(320.0f + legSeparation, 180.0f + upperLegs, 20.0f));	// 11
	_constraints.push_back(new LinearConstraint(_points[9], _points[10]));
	_constraints.push_back(new LinearConstraint(_points[9], _points[11]));
	_constraints.push_back(new LinearConstraint(_points[10], _points[11]));

	float knee = upperLegs + 80.0f;
	_points.push_back(new PointMass(320.0f - legSeparation, 180.0f + knee, 20.0f));			// 12
	_points.push_back(new PointMass(320.0f + legSeparation, 180.0f + knee, 20.0f));			// 13
	_constraints.push_back(new LinearConstraint(_points[10], _points[12]));
	_constraints.push_back(new LinearConstraint(_points[11], _points[13]));

	float lowerLegs = knee + 80.0f;
	_points.push_back(new PointMass(320.0f - legSeparation, 180.0f + lowerLegs, 20.0f));	// 14
	_points.push_back(new PointMass(320.0f + legSeparation, 180.0f + lowerLegs, 20.0f));	// 15
	_constraints.push_back(new LinearConstraint(_points[12], _points[14]));
	_constraints.push_back(new LinearConstraint(_points[13], _points[15]));


	// Angular constraints
	// Head
	_constraints.push_back(new AngularConstraint(_points[0], _points[2], distanceBetween(_points[0]->getPosition(), _points[2]->getPosition()) - 30.0f));
	_constraints.push_back(new AngularConstraint(_points[0], _points[3], distanceBetween(_points[0]->getPosition(), _points[3]->getPosition()) - 30.0f));
	// Left shoulder
	_constraints.push_back(new AngularConstraint(_points[1], _points[5], 80.0f));
	// Right shoulder
	_constraints.push_back(new AngularConstraint(_points[1], _points[6], 80.0f));
	// Left elbow
	_constraints.push_back(new AngularConstraint(_points[2], _points[7], 45.0f));
	// Right elbow
	_constraints.push_back(new AngularConstraint(_points[3], _points[8], 45.0f));
	// Rib cage 
	_constraints.push_back(new AngularConstraint(_points[2], _points[10], distanceBetween(_points[2]->getPosition(), _points[10]->getPosition()) - 20.0f));
	_constraints.push_back(new AngularConstraint(_points[3], _points[11], distanceBetween(_points[3]->getPosition(), _points[11]->getPosition()) - 20.0f));
	// Middle back
	//_constraints.push_back(new AngularConstraint(_points[4], _points[10], 20.0f));
	//_constraints.push_back(new AngularConstraint(_points[4], _points[11], 20.0f));
	// Pelvis
	//_constraints.push_back(new AngularConstraint(_points[3], _points[12], 80.0f));
	// Left leg
	_constraints.push_back(new AngularConstraint(_points[9], _points[13], distanceBetween(_points[10]->getPosition(), _points[13]->getPosition()) - 2.0f));
	// Right leg
	_constraints.push_back(new AngularConstraint(_points[9], _points[14], distanceBetween(_points[10]->getPosition(), _points[14]->getPosition()) - 2.0f));
	// Left knee
	_constraints.push_back(new AngularConstraint(_points[15], _points[11], 80.0f));
	// Right knee
	_constraints.push_back(new AngularConstraint(_points[14], _points[10], 80.0f));
	// Dont cross knees
	//_constraints.push_back(new AngularConstraint(_points[13], _points[14], 30.0f));



	for (auto& p : _points) {
		p->setOldPosition(p->getPosition());
		_constraints.push_back(new NotUnderScreenConstraint(p));
	}
}
#pragma endregion


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


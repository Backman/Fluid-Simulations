#pragma once

#include "VectorUtil.h"
#include "PointMass.h"
#include <SFML\Graphics.hpp>

class Constraint {
public:
	Constraint() {}
	virtual ~Constraint() {}

	virtual void applyConstraint() = 0;
	virtual void render(sf::RenderWindow* rw) {}
};

class LinearConstraint : public Constraint {
public:
	LinearConstraint(PointMass* p1, PointMass* p2) :
		_joint1(p1), _p2(p2)
	{
		_restLength = distanceBetween(p1->getPosition(), p2->getPosition());
	}

	~LinearConstraint()
	{
		/*if (_p1 != nullptr) {
			delete _p1;
			_p1 = nullptr;
		}
		if (_p2 != nullptr) {
			delete _p2;
			_p2 = nullptr;
		}*/
	}

	virtual void applyConstraint() override;
	virtual void render(sf::RenderWindow* rw) override;

private:
	PointMass* _joint1;
	PointMass* _p2;

	float _restLength;
};

class AngularConstraint : public Constraint {
public:
	AngularConstraint(PointMass* p1, PointMass* p2, float restLenght) :
		_p1(p1), _p2(p2), _restLength(restLenght)
	{}

	virtual void applyConstraint() override;
	virtual void render(sf::RenderWindow* rw) override;

private:
	PointMass* _p1;
	PointMass* _p2;
	float _restLength;
};

class RotationConstraint : public Constraint {
public:
	RotationConstraint(PointMass* j1, PointMass* j2, PointMass* j3, float minAngle, float maxAngle) :
		_joint1(j1), _joint2(j2), _joint3(j3), _minAngle(minAngle), _maxAngle(maxAngle)
	{}

	~RotationConstraint()
	{
		/*if (_p1 != nullptr) {
			delete _p1;
			_p1 = nullptr;
		}
		if (_p2 != nullptr) {
			delete _p2;
			_p2 = nullptr;
		}*/
	}

	virtual void applyConstraint() override;
	virtual void render(sf::RenderWindow* rw) override;

private:
	PointMass* _joint1;
	PointMass* _joint2;
	PointMass* _joint3;
	float _minAngle, _maxAngle;
};

class NotUnderScreenConstraint : public Constraint {
public:
	NotUnderScreenConstraint(PointMass* p) :
		_p(p)
	{}

	virtual void applyConstraint() override {
		if(_p->getPosition().y > 768.0f) {
			_p->setPosition(sf::Vector2f(_p->getPosition().x, 768.0f));
		}
	}

private:
	PointMass* _p;
};

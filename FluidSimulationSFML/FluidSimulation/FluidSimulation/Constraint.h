#pragma once

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
		_p1(p1), _p2(p2)
	{}

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
	PointMass* _p1;
	PointMass* _p2;
};

class RotationConstraint : public Constraint {
public:
	RotationConstraint(PointMass* p1, PointMass* p2, float angle) :
		_p1(p1), _p2(p2), _angle(angle)
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
	PointMass* _p1;
	PointMass* _p2;
	float _angle;
};

class FixedDistanceConstraint : public Constraint {
public:
	FixedDistanceConstraint(PointMass* p1, PointMass* p2, float restLength) :
		_p1(p1), _p2(p2), _restLength(restLength)
	{}

	virtual void applyConstraint() override;
	virtual void render(sf::RenderWindow* rw) override;

private:
	PointMass* _p1;
	PointMass* _p2;
	float _restLength;
};

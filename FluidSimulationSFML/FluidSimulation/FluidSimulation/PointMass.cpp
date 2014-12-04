#include "PointMass.h"

PointMass::PointMass() :
	_position()
{
	setMass(0.1f);
}

PointMass::PointMass(const sf::Vector2f& pos, float mass) :
	_position(pos)
{
	setMass(mass);
}

PointMass::PointMass(float xPos, float yPos, float mass) :
	_position(xPos, yPos)
{
	setMass(mass);
}


PointMass::~PointMass()
{
}

void PointMass::setMass(float newMass) {
	_mass = newMass;

	if (_mass != 0.0) {
		_invMass = 1.0 / _mass;
	}
	else {
		_invMass = std::numeric_limits<float>::max();
	}
}

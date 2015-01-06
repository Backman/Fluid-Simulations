#include "PointMass.h"

PointMass::PointMass(float xPos, float yPos, float mass) :
	_position(xPos, yPos), _shape(5.0f)
{
	_shape.setFillColor(sf::Color::Red);
	_shape.setOrigin(5.0f, 5.0f);

	setMass(mass);
}


PointMass::~PointMass()
{
}

void PointMass::setMass(float newMass) {
	_mass = newMass;

	if (_mass != 0.0f) {
		_invMass = 1.0f / _mass;
	} else {
		_invMass = std::numeric_limits<float>::max();
	}
}

void PointMass::render(sf::RenderWindow* rw) {
	_shape.setPosition(_position);
	rw->draw(_shape);

	sf::Vertex line[] = {
		sf::Vertex(_position, sf::Color::Green),
		sf::Vertex(_position + _force * 0.1f, sf::Color::Green)
	};
	
	rw->draw(line, 2, sf::Lines);
}

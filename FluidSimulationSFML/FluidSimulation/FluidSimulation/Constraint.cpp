#include "Constraint.h"
#include "VectorUtil.h"

void LinearConstraint::applyConstraint() {

}

void LinearConstraint::render(sf::RenderWindow* rw) {
	sf::Vertex line[] = {
		sf::Vertex(_p1->getPosition()),
		sf::Vertex(_p2->getPosition())
	};

	
	rw->draw(line, 2, sf::Lines);
}

void RotationConstraint::applyConstraint() {

}

void RotationConstraint::render(sf::RenderWindow* rw) {

}

void FixedDistanceConstraint::applyConstraint() {
	
	sf::Vector2f& x1 = _p1->getPosition();
	sf::Vector2f& x2 = _p2->getPosition();
	sf::Vector2f delta = x2 - x1;

	float deltaLength = sqrt(dot(delta, delta));
	float diff = (deltaLength - _restLength) / (deltaLength * (_p1->getInvMass() + _p2->getInvMass()));

	x1 += _p1->getInvMass() * delta * diff;
	x2 -= _p2->getInvMass() * delta * diff;
}

void FixedDistanceConstraint::render(sf::RenderWindow* rw) {

}

#include "Constraint.h"
#include "VectorUtil.h"

void LinearConstraint::applyConstraint() {
	sf::Vector2f& x1 = _p1->getPosition();
	sf::Vector2f& x2 = _p2->getPosition();
	sf::Vector2f delta = x2 - x1;

	float deltaLength = magnitude(delta);
	float diff = (deltaLength - _restLength) / (deltaLength * (_p1->getInvMass() + _p2->getInvMass()));
	
	x1 += _p1->getInvMass() * delta * diff;
	x2 -= _p2->getInvMass() * delta * diff;
}

void LinearConstraint::render(sf::RenderWindow* rw) {
	sf::Vertex line[] = {
		sf::Vertex(_p1->getPosition()),
		sf::Vertex(_p2->getPosition())
	};
	
	rw->draw(line, 2, sf::Lines);
}

void RotationConstraint::applyConstraint() {
	sf::Vector2f& v1 = _joint1->getPosition();
	sf::Vector2f& v2 = _joint2->getPosition();
	sf::Vector2f& v3 = _joint3->getPosition();

	sf::Vector2f top = v1 - v2;
	sf::Vector2f bot = v3 - v2;
	float angle = angleBetween(top, bot);

	if (angle > _maxAngle) {
		
	} else if(angle < _minAngle) {

	}
}

void RotationConstraint::render(sf::RenderWindow* rw) {

}

void AngularConstraint::applyConstraint() {
	sf::Vector2f& v1 = _p1->getPosition();
	sf::Vector2f& v2 = _p2->getPosition();

	float length = distanceBetween(v1, v2);

	if (length < _restLength) {
		sf::Vector2f delta = v2 - v1;
		normalize(delta);

		float diff = _restLength - length;

		float totalMass = _p1->getMass() + _p2->getMass();

		v1 -= delta * diff * (_p1->getInvMass() / totalMass);
		v2 += delta * diff * (_p2->getInvMass() / totalMass);
	}
}

void AngularConstraint::render(sf::RenderWindow* rw) {

}

void MinMaxConstraint::applyConstraint() {
	sf::Vector2f& x = _p->getPosition();

	x = vMin(vMax(x, _min), _max);
}

void MinMaxConstraint::render(sf::RenderWindow* rw) {

}
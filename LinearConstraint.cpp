#pragma once


class LinearConstraint : public Constraint {
public:
	LinearConstraint(PointMass* p1, PointMass* p2, float length);
	~LinearConstraint();


	
private:
	PointMass* _p1;
	PointMass* _p2;
	float _length;
};


LinearConstraint::LinearConstraint(PointMass* p1, PointMass* p2, float length) : 
	_p1(p1), _p2(p2), _length(length)
{
}



LinearConstraint::applyConstraint() {
	sf::Vector2f& x1 = p1->getPosition();
	sf::Vector2f& x2 = p2->getPosition();

	sf::Vector2f dir = x2 - x1;
	normalize(dir);
	sf::Vector2f avg = (x2 + x1) / 2.0f;

	sf::Vector2f newPos1 = avg - dir * (_length / 2.0f);
	sf::Vector2f newPos2 = avg + dir * (_length / 2.0f);

	x1 += newPos1;
	x2 += newPos2;
}


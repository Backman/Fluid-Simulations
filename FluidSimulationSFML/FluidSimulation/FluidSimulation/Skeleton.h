#pragma once

#include <SFML\Graphics.hpp>
#include <queue>
#include <map>

class Constraint;
class PointMass;

class Skeleton
{
	struct ForceApplier {
		PointMass* point;
		sf::Vector2f force;
	};
	typedef std::map<PointMass*, sf::Vector2f>::iterator it_type;
public:
	Skeleton(float gravity);
	~Skeleton();

	void update(float timeStep);
	void render(sf::RenderWindow* rw);

	void addForce(const sf::Vector2f& force, PointMass* point);

	void addMouseForce(const sf::Vector2f& mousePos);
	void releaseMouse();

	void addConstraint(Constraint* constraint);
	void addPointMass(PointMass* pointMass);

	static void initHumanSkeleton(Skeleton* skeleton, bool randomPos = false);

private:
	void clearConstraints();
	void clearPoints();

	void verlet(float timeStep);
	void accumulateForces();
	void applyConstraints(int iterations);

	void addAngularConstraint(PointMass* p1, PointMass* p2, float dist);

	std::vector<PointMass*> _points;
	std::vector<Constraint*> _constraints;
	std::queue<ForceApplier> _forceQueue;
	PointMass* _nearestPoint;
	float _gravity;
	bool _mouseDown;
};


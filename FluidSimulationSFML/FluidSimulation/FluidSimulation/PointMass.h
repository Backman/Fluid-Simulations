#pragma once

#include <SFML\Graphics.hpp>

class PointMass
{
public:
	PointMass();
	PointMass(const sf::Vector2f& pos, float mass);
	PointMass(float xPos, float yPos, float mass);
	~PointMass();

	void setMass(float newMass);
	float getMass() const { return _mass; }
	float getInvMass() const { return _invMass; }

	void setPosition(const sf::Vector2f newPos, bool updateOldPosition = false) {
		_position = newPos;
		if (updateOldPosition) {
			setOldPosition(newPos);
		}
	}
	sf::Vector2f& getPosition() { return _position; }

	void setOldPosition(const sf::Vector2f& newPos) { _oldPosition = newPos; }
	sf::Vector2f& getOldPosition() { return _oldPosition; }
	

	sf::Vector2f& getForce() { return _force; }
	void clearForce() { _force = sf::Vector2f(); }
	void addForce(const sf::Vector2f& force) { _force += force; }

private:
	/** Current position */
	sf::Vector2f _position;
	/** Previous position */
	sf::Vector2f _oldPosition;
	/** The force */
	sf::Vector2f _force;

	/** The mass */
	float _mass;
	/** The inverse mass, 1.0f / mass */
	float _invMass;
};


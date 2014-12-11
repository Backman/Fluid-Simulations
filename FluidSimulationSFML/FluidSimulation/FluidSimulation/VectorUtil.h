#pragma once

#include <SFML\Graphics.hpp>

#define M_PI 3.14159265359

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

static sf::Vector2f vMin(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	sf::Vector2f ret;
	ret.x = std::min(v1.x, v2.x);
	ret.y = std::min(v1.y, v2.y);

	return ret;
}

static sf::Vector2f vMax(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	sf::Vector2f ret;
	ret.x = std::max(v1.x, v2.x);
	ret.y = std::max(v1.y, v2.y);

	return ret;
}

static float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

static float magnitudeSqr(const sf::Vector2f& v) {
	return dot(v, v);
}

static float magnitude(const sf::Vector2f& v) {
	return sqrt(dot(v, v));
}

static float distanceBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	sf::Vector2f diff = v1 - v2;
	return magnitude(diff);
}

static float cross(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

static float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return atan2(cross(v1, v2), dot(v1, v2));
}

static sf::Vector2f normalize(const sf::Vector2f& v) {
	sf::Vector2f ret;
	float len = magnitude(v);

	ret.x = v.x / len;
	ret.y = v.y / len;

	return ret;
}

static void rotateVector(sf::Vector2f& v, float angle) {
	float theta = degreesToRadians(angle);
	
	float cs = cos(theta);
	float sn = sin(theta);

	float newX = v.x * cs - v.y * sn;
	float newY = v.x * sn + v.y * cs;

	v.x = newX;
	v.y = newY;
}

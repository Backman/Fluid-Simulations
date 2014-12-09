#pragma once

#include <SFML\Graphics.hpp>

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


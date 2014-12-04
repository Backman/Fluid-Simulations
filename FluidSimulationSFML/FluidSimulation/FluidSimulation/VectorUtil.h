#pragma once

#include <SFML\Graphics.hpp>

sf::Vector2f vMin(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	sf::Vector2f ret;
	ret.x = std::min(v1.x, v2.x);
	ret.y = std::min(v1.y, v2.y);

	return ret;
}

sf::Vector2f vMax(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	sf::Vector2f ret;
	ret.x = std::max(v1.x, v2.x);
	ret.y = std::max(v1.y, v2.y);

	return ret;
}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
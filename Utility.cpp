#include "Utility.h"

#include "Object.h"

float dotProduct(sf::Vector2f & a, sf::Vector2f & b)
{
	return a.x * b.x + a.y * b.y;
}

sf::Vector2f getNormal(sf::Vector2f & a)
{
	return sf::Vector2f(-a.y, a.x);
}

float getVectorLength(sf::Vector2f & a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

sf::Vector2f normalizeVector(sf::Vector2f & a)
{
	return sf::Vector2f(a.x / getVectorLength(a), a.y / getVectorLength(a));
}

sf::Vector2f projectOnAxis(std::vector<sf::Vector2f>& vertices, sf::Vector2f & axis)
{
	float min = std::numeric_limits<float>::infinity();
	float max = -std::numeric_limits<float>::infinity();

	for (auto &vertex : vertices) {
		float projectionLength = dotProduct(vertex, axis);

		if (projectionLength < min) {
			min = projectionLength;
		}

		if (projectionLength > max) {
			max = projectionLength;
		}
	}

	return sf::Vector2f(min, max);
}

bool areOverlaping(sf::Vector2f & a, sf::Vector2f & b)
{
	return a.x <= b.y && a.y >= b.x;
}

float getOverlapLength(sf::Vector2f & a, sf::Vector2f & b)
{
	if (!areOverlaping(a, b)) {
		return 0.f;
	}

	return std::min(a.y, b.y) - std::max(a.x, b.x);
}

bool checkCollision(Object& object1, Object& object2)
{
	std::vector<sf::Vector2f> axes1 = object1.getAxes();
	std::vector<sf::Vector2f> axes2 = object2.getAxes();

	std::vector<sf::Vector2f> vertices1 = object1.getVertices();
	std::vector<sf::Vector2f> vertices2 = object2.getVertices();

	for (auto &axis : axes1) {
		sf::Vector2f projection1 = projectOnAxis(vertices1, axis);
		sf::Vector2f projection2 = projectOnAxis(vertices2, axis);

		if (!areOverlaping(projection1, projection2)) {
			return false;
		}
	}

	for (auto &axis : axes2) {
		sf::Vector2f projection1 = projectOnAxis(vertices1, axis);
		sf::Vector2f projection2 = projectOnAxis(vertices2, axis);

		if (!areOverlaping(projection1, projection2)) {
			return false;
		}
	}

	return true;;
}

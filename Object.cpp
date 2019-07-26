#include "Object.h"

#define PI 3.14159265

Object::Object(int n, sf::Vector2f position) {
	float radius = 100.f;

	for (int i = 0; i < n; ++i) {
		float x = radius * cos(2 * PI * i / n);
		float y = radius * sin(2 * PI * i / n);

		m_vertices.push_back(sf::Vector2f(x, y));
	}

	float sumX = 0, sumY = 0;
	for (int i = 0; i < n; ++i) {
		sumX += m_vertices[i].x;
		sumY += m_vertices[i].y;
	}

	setOrigin(sumX / n, sumY / n);
	setPosition(position);
}

std::vector<sf::Vector2f> Object::getVertices() const
{
	std::vector<sf::Vector2f> transformedVertices;

	for (auto &vertex : m_vertices) {
		transformedVertices.push_back(getTransform().transformPoint(vertex));
	}

	return transformedVertices;
}

std::vector<sf::Vector2f> Object::getAxes() const
{
	std::vector<sf::Vector2f> axes;
	std::vector<sf::Vector2f> vertices = getVertices();

	for (int i = 0; i < vertices.size(); ++i) {
		sf::Vector2f edge(vertices[(i + 1) % vertices.size()] - vertices[i % vertices.size()]);
		sf::Vector2f normal = getNormal(edge);

		axes.push_back(normalizeVector(normal));
	}

	return axes;
}

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	sf::ConvexShape polygon;
	polygon.setPointCount(m_vertices.size());
	polygon.setFillColor(sf::Color::Red);
	for (int i = 0; i < m_vertices.size(); ++i) {
		polygon.setPoint(i, m_vertices[i]);
	}

	target.draw(polygon, states);

	for (auto &vertex : m_vertices) {
		sf::CircleShape circle;
		circle.setRadius(5.f);
		circle.setPosition(vertex);
		circle.setOrigin(sf::Vector2f(5.f, 5.f));

		target.draw(circle, states);
	}
}

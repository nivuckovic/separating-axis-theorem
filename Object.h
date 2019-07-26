#pragma once

#include "SFML\Graphics.hpp"
#include <vector>
#include "Utility.h"

class Object : public sf::Transformable, public sf::Drawable
{
public:
	Object(int n, sf::Vector2f position);

	std::vector<sf::Vector2f> getVertices() const;
	std::vector<sf::Vector2f> getAxes() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<sf::Vector2f> m_vertices;

};


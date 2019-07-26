#pragma once

#include "SFML\Graphics.hpp"

float dotProduct(sf::Vector2f &a, sf::Vector2f &b);

sf::Vector2f getNormal(sf::Vector2f &a);

float getVectorLength(sf::Vector2f &a);

sf::Vector2f normalizeVector(sf::Vector2f &a);

sf::Vector2f projectOnAxis(std::vector<sf::Vector2f> &vertices, sf::Vector2f &axis);

bool areOverlaping(sf::Vector2f &a, sf::Vector2f &b);

float getOverlapLength(sf::Vector2f &a, sf::Vector2f &b);


class Object;
bool checkCollision(Object &object1, Object &object2);
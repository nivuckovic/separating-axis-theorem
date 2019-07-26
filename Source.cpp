#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Object.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	Object object1(4, sf::Vector2f(300.f, 300.f));
	Object object2(3, sf::Vector2f(600.f, 600.f));

	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock m_clock;
	sf::Time m_elapsedTime;
	while (window.isOpen())
	{
		m_elapsedTime += m_clock.restart();
		while (m_elapsedTime.asSeconds() >= timePerFrame.asSeconds()) {
			m_elapsedTime -= timePerFrame;

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Right) {
						object1.rotate(15.f);
					}
				}

				sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

				object1.setPosition(mousePosition);
			}
			
			printf("%d\n", checkCollision(object1, object2));
		}

		window.clear();

		window.draw(object2);
		window.draw(object1);

		window.display();

	}

	return 0;
}
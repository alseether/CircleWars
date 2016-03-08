#include "SFML\Graphics.hpp"
#include "Circle.hpp"
//#include <iostream>

int main(){
	float radio = 100;
	sf::VideoMode videoMode = sf::VideoMode(800, 800);
	sf::RenderWindow window(videoMode, "Circle Wars");
	Circle prueba(sf::Vector2f(400, 400), radio, 200, 1, sf::Color::Green);
	while (window.isOpen()){
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)){
			switch (event.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
					prueba.rotateLeft(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
					prueba.rotateRight(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
					prueba.setColor(sf::Color::Blue);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
					prueba.setDegrees(90);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
					prueba.setFacing(270);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
					prueba.setPosition(sf::Vector2f(200, 200));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
					prueba.setRadius(50);
				}
				break;
			}
		}

		window.draw(prueba);
		window.display();
	}

	return 0;
}
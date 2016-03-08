#include "SFML\Graphics.hpp"
#include "Circle.hpp"
#include "CirclePlayer.hpp"

#define DEBUG

int main(){
	float radio = 100;
	sf::VideoMode videoMode = sf::VideoMode(800, 800);
	sf::RenderWindow window(videoMode, "Circle Wars");
	CirclePlayer prueba(sf::Vector2f(400, 400));
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
					prueba.rotateLeft(2);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
					prueba.rotateRight(2);
				}
				/*
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
				}*/
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
					prueba.setDegrees(270);
				}
				break;
			}
		}
		sf::Vector2i puntero = sf::Mouse::getPosition(window);
		if (prueba.isPointVulnerable(puntero)){
			prueba.setColor(sf::Color::Red);
			prueba.reduceHealth(1);
		}
		else if (prueba.isPointProtected(puntero)){
			prueba.setColor(sf::Color::Yellow);
			prueba.increaseHealth(1);
		}
		else{
			prueba.setColor(sf::Color::Green);
		}
		if (!prueba.isAlive()){
			prueba.setColor(sf::Color::Red);
		}

		window.draw(prueba);
		window.display();
	}

	return 0;
}
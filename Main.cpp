#include "SFML\Graphics.hpp"
#include "Circle.hpp"
#include "CirclePlayer.hpp"
#include "CircleEnemy.hpp"
#include "GameEngine.hpp"

#define DEBUG

int main(){
	sf::VideoMode videoMode = sf::VideoMode(800, 800);
	sf::RenderWindow window(videoMode, "Circle Wars");
	GameEngine eng(sf::Vector2f(800, 800), 15);

	sf::Clock clock;

	while (window.isOpen()){
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)){
			switch (event.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				eng.keyPressed();
				break;
			}
		}
		sf::Time elapsed = clock.restart();
		eng.update(elapsed);
		window.draw(eng);
		window.display();
	}

	return 0;
}
#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML\Graphics.hpp>
#include "CirclePlayer.hpp"
#include "CircleEnemy.hpp"

/*
PENDIENTE:
	- Comenzar a mover el juego (crear los disparos, etc)
	- Comunicar los eventos de main con lel motor
	- Textura de fondo
	- Evitar enemigos superpuestos ??
*/

class GameEngine : public sf::Drawable{
public:
	GameEngine(sf::Vector2f screenRes, int nEnemies){
		std::srand(time(NULL));
		this->player = new CirclePlayer(sf::Vector2f(screenRes.x/2, screenRes.y/2));
		this->screenRes = screenRes;
		for (std::size_t i = 0; i < nEnemies; ++i){
			float posX, posY;
			posX = std::rand() % int(screenRes.x);
			while (posX >= screenRes.x * 0.4 && posX <= screenRes.x * 0.6) posX = std::rand() % int(screenRes.x);
			if (posX < 25) posX += 25;
			if (posX > screenRes.x-25) posX -= 25;
			posY = std::rand() % int(screenRes.y);
			while (posY >= screenRes.y * 0.4 && posY <= screenRes.y * 0.6) posY = std::rand() % int(screenRes.y);
			if (posY < 25) posY += 25;
			if (posY > screenRes.y - 25) posY -= 25;
			CircleEnemy e(sf::Vector2f(posX,posY));
			e.trackPlayer(this->player->getPosition());
			this->enemies.push_back(e);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(*this->player, states);
		for (std::size_t i = 0; i < enemies.size(); ++i){
			target.draw(enemies[i], states);
		}
	}

private:
	sf::Vector2f screenRes;
	CirclePlayer* player;
	std::vector<CircleEnemy> enemies;

};

#endif
#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML\Graphics.hpp>
#include "CirclePlayer.hpp"
#include "CircleEnemy.hpp"
#include "CircleBullet.hpp"

/*
PENDIENTE:
	- Comenzar a mover el juego (crear los disparos, etc)
	- Comunicar los eventos de main con del motor
	- Textura de fondo
	- Evitar enemigos superpuestos ??
*/

class GameEngine : public sf::Drawable{
public:
	GameEngine(sf::Vector2f screenRes, int nBullets){
		std::srand(time(NULL));
		this->player = new CirclePlayer(sf::Vector2f(screenRes.x/2, screenRes.y/2));
		this->screenRes = screenRes;
		/*
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
		}*/
		for (std::size_t i = 0; i < nBullets; ++i){
			CircleBullet b(sf::Vector2f(0,0));
			b.resetBullet(screenRes);
			this->bullets.push_back(b);
		}
	}

	void keyPressed(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			player->rotateLeft(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			player->rotateRight(2);
		}
	}

	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < bullets.size(); ++i)
		{
			CircleBullet& p = bullets[i];

			if (p.getColor() == sf::Color::Green){
				p.lifeTime -= elapsed;
			}

			if (!p.isAlive()){
				p.setColor(sf::Color(255, 127, 39));
			}

			sf::Vector2f newPos = p.getPosition();
			newPos += p.velocity * elapsed.asSeconds();

			if (newPos.x <= (0 + p.getRadius()) || newPos.x >= (screenRes.x - p.getRadius())){
				p.velocity.x = -p.velocity.x;
			}

			if (newPos.y <= (0 + p.getRadius()) || newPos.y >= (screenRes.y - p.getRadius())){
				p.velocity.y = -p.velocity.y;
			}

			p.setPosition(newPos);

			if (p.getColor() != sf::Color::Green){
				if (player->isPointVulnerable(p.getPosition())){
					player->reduceHealth(5);
					p.velocity = -p.velocity;
				}
			}
			if (player->isPointProtected(p.getPosition())){
				p.setColor(sf::Color::Green);
				p.lifeTime = sf::seconds(4);
				p.velocity = -p.velocity;
			}
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(*this->player, states);
		for (std::size_t i = 0; i < bullets.size(); ++i){
			//target.draw(enemies[i], states);
			target.draw(bullets[i], states);
		}
	}

private:
	sf::Vector2f screenRes;
	CirclePlayer* player;
	//std::vector<CircleEnemy> enemies;
	std::vector<CircleBullet> bullets;

	void solveCollision(CircleBullet& p){
		if (p.getPosition().x <= player->getPosition().x){
			if (p.getPosition().y <= player->getPosition().y){
				
			}
			else{
				
			}
		}
		else{
			if (p.getPosition().y <= player->getPosition().y){
				
			}
			else{
				
			}
		}
	}


};

#endif
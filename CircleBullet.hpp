#ifndef CIRCLEBULLET_HPP
#define CIRCLEBULLET_HPP

#include "Circle.hpp"
#include "Circumference.hpp"
#include <SFML\Graphics.hpp>


class CircleBullet : public Circle{
public:
	CircleBullet(sf::Vector2f pos) : 
		Circle(pos, 3, 360, 0, sf::Color(255,127,39)) // Orange
	{
		sf::Color c = this->inner->getFillColor();
		c.a = 60;
		this->inner->setFillColor(c);
		this->inner->setRadius(3);
		this->inner->setPosition(sf::Vector2f(pos.x-5, pos.y-3));

		lifeTime = sf::seconds(4);

		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 100) + 50.f;
		velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	}

	void setPosition(sf::Vector2f pos){
		this->pos = pos;
		this->inner->setPosition(pos.x - radius, pos.y - radius);
		calculateVtx();
	}

	void resetBullet(sf::Vector2f limit){
		float posX, posY;
		posX = std::rand() % int(limit.x);
		while (posX >= limit.x * 0.4 && posX <= limit.x * 0.6) posX = std::rand() % int(limit.x);
		if (posX < 3) posX += 3;
		if (posX > limit.x - 3) posX -= 3;
		posY = std::rand() % int(limit.y);
		while (posY >= limit.y * 0.4 && posY <= limit.y * 0.6) posY = std::rand() % int(limit.y);
		if (posY < 3) posY += 3;
		if (posY > limit.y - 3) posY -= 3;

		this->setPosition(sf::Vector2f(posX, posY));
		lifeTime = sf::seconds(4);
		this->setColor(sf::Color(255, 127, 39));
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	}

	bool isAlive(){
		return (lifeTime > sf::Time::Zero);
	}

	sf::Vector2f velocity;
	sf::Time lifeTime;

};

#endif
#ifndef CIRCLEPLAYER_HPP
#define CIRCLEPLAYER_HPP

#include "Circle.hpp"
#include <SFML\Graphics.hpp>

class CirclePlayer : public Circle{
public:
	Circle(sf::Vector2f pos){
		this->pos = pos;
		this->radius = 50;
		this->inner = new sf::CircleShape(50 - 3);
		sf::Color innerColor = sf::Color::Green;
		innerColor.a *= 0.05;
		this->inner->setFillColor(innerColor);
		this->inner->setPosition(pos.x - 50 + 3, pos.y - 50 + 3);
		this->degrees = 270;
		this->color = color;
		this->facing = 90;
		this->vtx = new sf::VertexArray(sf::LinesStrip);
		calculateVtx();
	}

	bool isPointinside(sf::Vector2i point){
		if (point.x >= 0 && point.y >= 0){
			float a = (point.x - pos.x) * (point.x - pos.x);
			float b = (point.y - pos.y) * (point.y - pos.y);
			return (a + b) < (radius*radius);
		}
		return false;
	}

	bool isPointVulnerable(sf::Vector2i point){
		if (isPointInside(point)){

		}
		return false;
	}

private:
	int life;
};

#endif
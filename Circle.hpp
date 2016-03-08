#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "SFML\Graphics.hpp"
#include <iostream>

class Circle : public sf::Drawable{
public:
	Circle(sf::Vector2f pos, int radius, int degrees, int facing, sf::Color color){
		this->pos = pos;
		this->radius = radius;
		this->inner = new sf::CircleShape(radius - 3);
		sf::Color innerColor = color;
		innerColor.a *= 0.05;
		this->inner->setFillColor(innerColor);
		this->inner->setPosition(pos.x-radius+3, pos.y-radius+3);
		this->degrees = degrees;
		this->color = color;
		this->facing = facing;
		this->vtx = new sf::VertexArray(sf::LinesStrip);
		calculateVtx();
	}

	sf::Vector2f getPosition(){
		return this->pos;
	}

	int getRadius(){
		return this->radius;
	}

	sf::Color getColor(){
		return this->color;
	}

	int getFacing(){
		return this->facing;
	}

	int getDegrees(){
		return this->degrees;
	}


	void setPosition(sf::Vector2f pos){
		this->pos = pos;
		this->inner->setPosition(pos.x - radius + 3, pos.y - radius + 3);
		calculateVtx();
	}

	void setRadius(int radius){
		this->radius = radius;
		this->inner->setRadius(radius);
		this->inner->setPosition(pos.x - radius + 3, pos.y - radius + 3);
		calculateVtx();
	}

	void setColor(sf::Color color){
		this->color = color;
		sf::Color innerColor = color;
		innerColor.a *= 0.05;
		this->inner->setFillColor(innerColor);
		calculateVtx();
	}

	void setFacing(int facing){
		this->facing = facing;
		calculateVtx();
	}

	void setDegrees(int degrees){
		degrees = int(degrees) % 360;
		this->degrees = degrees;
		calculateVtx();
	}


	void rotateLeft(int degrees){
		this->facing = (facing + degrees) % 360;
		calculateVtx();
	}

	void rotateRight(int degrees){
		this->facing = (facing - degrees) > 0 ? (facing - degrees) : 360 + (facing - degrees);
		calculateVtx();
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(*this->vtx, states);
		target.draw(*this->inner, states);
	}

protected:
	void calculateVtx(){
		int margin = 5;
		this->vtx->clear();
		int origin = facing + (degrees/2);
		for (int i = 0; i < degrees; ++i){
			int actualDegree = (origin - i) % 360;
			if (actualDegree < 0) actualDegree = 360 + actualDegree;
			sf::Vector2f vertexPos;
			vertexPos.x = pos.x + (std::cos(actualDegree * 3.14159 / 180) * radius);
			vertexPos.y = pos.y - (std::sin(actualDegree * 3.14159 / 180) * radius);
			if (actualDegree >= (facing - margin) && actualDegree <= (facing + margin)){
				this->vtx->append(sf::Vertex(vertexPos, sf::Color::White));
			}
			else
				this->vtx->append(sf::Vertex(vertexPos, color));
		}
	}

protected:
	sf::VertexArray* vtx;
	sf::Color color;
	sf::CircleShape* inner;
	int radius;
	int degrees;
	int facing;
	sf::Vector2f pos;
};

#endif
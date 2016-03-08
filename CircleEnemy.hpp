#ifndef CIRCLEENEMY_HPP
#define CIRCLEENEMY_HPP

#include "Circle.hpp"
#include "Circumference.hpp"
#include <SFML\Graphics.hpp>

//#define DEBUG

class CircleEnemy : public Circle{
public:
	CircleEnemy(sf::Vector2f pos) : 
		Circle(pos, 25, 180, 90, sf::Color::Red)
	{
		this->outterCirc = new Circumference(this->pos, this->radius + 3);
		this->innerCirc = new Circumference(this->pos, this->radius - 3);
	}

	void trackPlayer(sf::Vector2f playerPos){
		if (this->pos.x <= playerPos.x){
			if (this->pos.y <= playerPos.y){
				// This Enemy circle is on the upper-left side of the player
				this->facing = 315;
			}
			else{
				// This Enemy circle is on the bottom-left side of the player
				this->facing = 45;
			}
		}
		else{
			if (this->pos.y <= playerPos.y){
				// This Enemy circle is on the upper-right side of the player
				this->facing = 225;
			}
			else{
				// This Enemy circle is on the bottom-right side of the player
				this->facing = 135;
			}
		}
		calculateVtx();
	}

	void reduceHealth(int amount){
		this->degrees -= amount;
		if (this->degrees < 0) this->degrees = 0;
	}

	void increaseHealth(int amount){
		this->degrees += amount;
		if (this->degrees > 360) this->degrees = 360;
	}

	bool isAlive(){
		return this->degrees > 0;
	}

	bool isPointProtected(sf::Vector2i point){
		sf::Vector2f pointAux(point.x, point.y);
		if (this->outterCirc->isInside(pointAux)){
			if (!this->innerCirc->isInside(pointAux)){
				Circumference auxCir(pointAux, 4);
				for (int i = 0; i < this->vtx->getVertexCount(); ++i){
					sf::Vertex v = (*(this->vtx))[i];
					if (auxCir.isInside(v.position)){
						return true;
					}
				}
				return false;
			}
		}
		return false;
	}

	bool isPointVulnerable(sf::Vector2i point){
		sf::Vector2f pointAux(point.x, point.y);
		if (this->outterCirc->isInside(pointAux)){
			if (!this->innerCirc->isInside(pointAux)){
				Circumference auxCir(pointAux, 4);
				for (int i = 0; i < this->vtx->getVertexCount(); ++i){
					sf::Vertex v = (*(this->vtx))[i];
					if (auxCir.isInside(v.position)){
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}

#ifdef DEBUG

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(*this->vtx, states);
		target.draw(*this->inner, states);
		this->outterCirc->draw(&target);
		this->innerCirc->draw(&target);
	}

#endif
private:
	Circumference* outterCirc;
	Circumference* innerCirc;
};

#endif
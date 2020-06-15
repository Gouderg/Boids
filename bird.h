#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "flock.h"
#include "mouvVec.h"

class Flock;
class MouvVec;

class Bird {
	
	public:
		Flock *flock;
		Bird(int id, int r, int g, int b, int angle, int x, int y, int z);
		~Bird();
		
		int getId() const {return this->id;}
		int getAngle() const {return this->angle;}
		int getR() const {return color[0];}
		int getG() const {return color[1];}
		int getB() const {return color[2];}

		void drawBird(sf::RenderWindow *window, int sizeBird);
		MouvVec *getPosition() const {return this->position;}


	private:
		MouvVec *position;
		int angle, id;
		int color[3];
};
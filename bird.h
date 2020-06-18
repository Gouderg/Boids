#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "flock.h"
#include "mouvVec.h"

class Flock;
class MouvVec;

class Bird {
	
	public:
		Flock *flock;
		Bird(int id, int r, int g, int b, double xPos, double yPos, double zPos);
		~Bird(){};
		
		int getId() const {return this->id;}
		int getAngle() const {return this->angle;}
		int getR() const {return color[0];}
		int getG() const {return color[1];}
		int getB() const {return color[2];}

		void update(Flock nuee);
		void drawBird(sf::RenderWindow *window, int sizeBird);
		
		MouvVec cohesion(MouvVec position, Flock nuee, int id);

		MouvVec* limitVitesse(MouvVec* velocite, double vitesseMax);
		MouvVec* getPosition() const {return this->position;}
		MouvVec* getVelocite() const {return this->velocite;}



	private:
		MouvVec *position;
		MouvVec *velocite;
		int angle, id;
		int color[3];
};
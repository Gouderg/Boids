#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <typeinfo>

#include "flock.h"
#include "mouvVec.h"

class Flock;
class MouvVec;

class Bird {
	
	public:
		Flock *flock;

		Bird(int id, int r, int g, int b, double x, double y, double z);
		~Bird(){};
		
		// Getter
		int getId() const {return this->id;}
		int getR() const {return color[0];}
		int getG() const {return color[1];}
		int getB() const {return color[2];}
		MouvVec* getPosition() const {return this->position;}
		MouvVec* getVelocity() const {return this->velocity;}

		// Update
		void update(Flock nuee);
		void drawBird(sf::RenderWindow *window, int sizeBird, int id);
		
		// Rules
		MouvVec cohesion(MouvVec position, Flock nuee, int id);
		MouvVec separation(MouvVec position, Flock nuee, int id);
		MouvVec alignment(MouvVec velocity, MouvVec position, Flock nuee, int id);

		void limit(MouvVec* vecteur, double valMax);
		void checkEdges(Flock nuee);
		void countNeighbours(Flock nuee, MouvVec position, int id);



	private:
		MouvVec *position;
		MouvVec *velocity;
		int id;
		int color[3];
};
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

		Bird(int id, int r, int g, int b, double xPos, double yPos, double zPos);		// Constructeur
		~Bird(){};																		// Destructeur
		
		// Getter
		int getId() const {return this->id;}											
		float getAngle() const {return this->angle;}
		int getR() const {return color[0];}
		int getG() const {return color[1];}
		int getB() const {return color[2];}
		MouvVec* getPosition() const {return this->position;}
		MouvVec* getVelocite() const {return this->velocite;}

		// Update la position de l'oiseau
		void update(Flock nuee);
		void drawBird(sf::RenderWindow *window, int sizeBird, int id);
		
		// Règles d'un boid
		MouvVec cohesion(MouvVec position, Flock nuee, int id);
		MouvVec separation(MouvVec position, Flock nuee, int id);
		MouvVec alignement(MouvVec velocite, MouvVec position, Flock nuee, int id);

		
		void limitVelocite(MouvVec* velocite, double vitesseMax);
		void checkEdges(Flock nuee);
		void countNeighbours(Flock nuee, MouvVec position, int id);



	private:
		MouvVec *position;
		MouvVec *velocite;
		float angle;
		int id;
		int color[3];
};
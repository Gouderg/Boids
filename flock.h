#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "bird.h"
#include "mouvVec.h"

class Bird;
class MouvVec;

class Flock {
	public:

		const int SIZE_W = 800;
		const int SIZE_H = 600;
		const int SIZE_D = 1;	


		Flock(); 	// Constructeur
		~Flock(){};	// Destructeur
			
		void display();  // Affiche l'id

		std::vector<Bird*> getBirds() const {return this->birds;}
		int getSizeBird() const {return sizeBird;}
		int getNbBird() const {return nbBird;};

	private:
		std::vector<Bird*> birds;
		int nbBird = 200;
		const int sizeBird = SIZE_W * 0.01;
		const int sizeBirdCollision = sizeBird * 4;
};
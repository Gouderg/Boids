#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "bird.h"

class Bird;

class Flock {
	public:

		const int SIZE_W = 800;
		const int SIZE_H = 600;	


		Flock(); 	// Constructeur
		~Flock();	// Destructeur
			
		void display();  // Affiche l'id

		std::vector<Bird> getBirds() const {return birds;}
		int getSizeBird() const {return sizeBird;}

	private:
		std::vector<Bird> birds;
		int nbBird = 10;
		int sizeBird = SIZE_W * 0.01;
};
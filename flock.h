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

		const double SIZE_W = 800;
		const double SIZE_H = 600;
		const double SIZE_D = 1;	


		Flock(); 	// Constructeur
		~Flock(){};	// Destructeur
			
		void display();  // Affiche l'id

		std::vector<Bird*> getBirds() const {return this->birds;}
		int getSizeBird() const {return sizeBird;}
		int getNbBird() const {return nbBird;};
		double getVitesseMax() const {return vitesseMax;}
		double getAttraction() const {return attraction;}

	private:
		std::vector<Bird*> birds;
		
		// Constante sur les caractéristiques des oiseaux
		const int nbBird = 50;									// Nombre d'oiseau
		const int sizeBird = SIZE_W * 0.01;						// Taille d'un oiseau
		const int sizeBirdCollision = sizeBird * 4;				// Taille de sa surface de collision
		const double vitesseMax = 6;							// Vitesse max des oiseaux
		const double attraction = 0.002;						// Attraction de l'oiseau vers le centre perçu
};	
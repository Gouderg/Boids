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

		const int SIZE_W = 1200;
		const int SIZE_H = 800;
		const int SIZE_D = 1;	


		Flock(); 	// Constructeur
		~Flock(){};	// Destructeur

		// Getter
		std::vector<Bird*> getBirds() const {return this->birds;}
		int getSizeBird() const {return sizeBird;}
		int getNbBird() const {return nbBird;};
		double getVitesseMax() const {return vitesseMax;}
		double getForceMax() const {return forceMax;}
		double getZoneAttraction() const {return zoneAttraction;}
		double getZoneAlignement() const {return zoneAlignement;}
		double getZoneRepulsion() const {return zoneRepulsion;}
		double getAttraction() const {return attraction;}
		double getRepulsion() const {return repulsion;}
		double getAlignement() const {return alignement;}

	private:
		std::vector<Bird*> birds;
		
		// Constantes sur les caractéristiques des oiseaux
		const int nbBird = 200;									// Nombre d'oiseaux
		const int sizeBird = 7;									// Taille d'un oiseau
		const double vitesseMax = 6;							// Vitesse max des oiseaux
		const double forceMax = 0.2;							// Force maximale supporté par un oiseau
		const double zoneAttraction = sizeBird * 12;			// Zone d'attraction pour le centre perçu
		const double zoneAlignement = sizeBird * 4;				// Zone d'orientation
		const double zoneRepulsion = sizeBird * 2;				// Zone de répulsion
		const double attraction = 0.01;							// Attraction de l'oiseau vers le centre perçu => 1%
		const double repulsion = 1;								// Répulsion des autre oiseau
		const double alignement = 1;
};	
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
		const int SIZE_H = 700;
		const int SIZE_D = 1;	


		Flock();
		~Flock(){};

		// Getter
		std::vector<Bird*> getBirds() const {return this->birds;}
		int getSizeBird() const {return sizeBird;}
		int getNbBird() const {return nbBird;};
		double getSpeedMax() const {return speedMax;}
		double getForceMax() const {return forceMax;}
		double getAttractionArea() const {return attractionArea;}
		double getAlignmentArea() const {return alignmentArea;}
		double getRepulsionArea() const {return repulsionArea;}
		double getAttraction() const {return attraction;}
		double getRepulsion() const {return repulsion;}
		double getAlignment() const {return alignment;}

	private:
		// Flock
		std::vector<Bird*> birds;
		
		// Constants about birds characteristics
		const int nbBird = 200;								// Numbers of bird
		const int sizeBird = 7;								// Size of bird
		const double speedMax = 6;							// Speed max
		const double forceMax = 0.2;						// Magnitude max
		const double attractionArea = sizeBird * 12;		// Attraction area pour le centre perçu
		const double alignmentArea = sizeBird * 4;			// Orientation area
		const double repulsionArea = sizeBird * 2;			// Repulsion area
		const double attraction = 0.02;						// Attraction force
		const double repulsion = 0.02;						// Repulsion force
		const double alignment = 1;							// Alignment force
};	
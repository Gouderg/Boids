#pragma once

#include <iostream>
#include "bird.h"
#include "flock.h"

class Bird;
class Flock;

class MouvVec {

	public:
		Flock *flock;
		Bird *bird;

		MouvVec(){};
		MouvVec(const double x, const double y, const double z);
		~MouvVec(){};

		// Opération de vecteur sur des vecteurs
		void addVec(MouvVec v);
		void subVec(MouvVec v);
		void divVec(MouvVec v);
		void mulVec(MouvVec v);

		// Opération de scalaire sur vecteur
		void addScal(double n);
		void subScal(double n);
		void divScal(double n);
		void mulScal(double n);

		// Norme du vecteur
		double normalize();

		// Setter
		void setX(const double x) {this->x = x;}
		void setY(const double y) {this->y = y;}
		void setZ(const double z) {this->z = z;}

		// Getter
		double getX() const {return this->x;}
		double getY() const {return this->y;}
		double getZ() const {return this->z;}



	private:
		double x, y, z;
};

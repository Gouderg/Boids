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
		MouvVec(const int x, const int y, const int z);
		~MouvVec(){};

		// Opération de vecteur sur des vecteurs
		void addVec(MouvVec v);
		void subVec(MouvVec v);
		void divVec(MouvVec v);
		void mulVec(MouvVec v);

		// Opération de scalaire sur vecteur
		void addScal(int n);
		void subScal(int n);
		void divScal(int n);
		void mulScal(int n);

		// Setter
		void setX(const int x) {this->x = x;}
		void setY(const int y) {this->y = y;}
		void setZ(const int z) {this->z = z;}

		// Getter
		int getX() const {return this->x;}
		int getY() const {return this->y;}
		int getZ() const {return this->z;}


	private:
		int x, y, z;
};

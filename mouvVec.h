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

		MouvVec(const int x, const int y, const int z);
		~MouvVec();

		void addVec(MouvVec v);


		void setX(const int x) {this->x = x;}
		void setY(const int y) {this->y = y;}
		void setZ(const int z) {this->z = z;}

		int getX() const {return this->x;}
		int getY() const {return this->y;}
		int getZ() const {return this->z;}


	private:
		int x, y, z;
};

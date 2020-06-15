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

		void setPosition(const int x, const int y, const int z);
		int getX() const {return this->x;}
		int getY() const {return this->y;}
		int getZ() const {return this->z;}


	private:
		int x, y, z;
};

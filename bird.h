#pragma once

#include <iostream>
#include "flock.h"

class Flock;


class Bird {
	
	public:
		
		Bird(int initId) : id(initId) {}
		~Bird();
		
		int getId() const {return this->id;}
		int getX() const {return this->x;}
		int getY() const {return this->y;}

		void setX(const int x) {this->x = x;}
		void setY(const int y) {this->y = y;}


	private:
		int x, y, id;

};
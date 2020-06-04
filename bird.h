#pragma once

#include <iostream>
#include "flock.h"

class Flock;


class Bird {
	
	public:
		
		Bird(int id, int r, int g, int b);
		~Bird();
		
		int getId() const {return this->id;}
		int getX() const {return this->x;}
		int getY() const {return this->y;}
		int getR() const {return color[0];}
		int getG() const {return color[1];}
		int getB() const {return color[2];}


		void setX(const int x) {this->x = x;}
		void setY(const int y) {this->y = y;}


	private:
		int x, y, id;
		int color[3];
};
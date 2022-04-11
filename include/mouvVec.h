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

		// Operation vector on vector
		void add(MouvVec v);
		void sub(MouvVec v);
		void div(MouvVec v);
		void mul(MouvVec v);

		// Operation scalar on vector
		void add(double n);
		void sub(double n);
		void div(double n);
		void mul(double n);

		// Static Operation between two vector.
		static MouvVec add(MouvVec v1, MouvVec v2);
		static MouvVec sub(MouvVec v1, MouvVec v2);
		static MouvVec div(MouvVec v1, MouvVec v2);
		static MouvVec mul(MouvVec v1, MouvVec v2);


		
		double magnitude();		// Magnitude of vector
		void setMag(double max);
		void normalize();						
		static double dist(MouvVec v1, MouvVec v2);	// Distance between 2 vector
		double headings();
		static double dotProduct(MouvVec v1, MouvVec v2);
		static double angleBetween(MouvVec v1, MouvVec v2);
		void limit(double max);
		static MouvVec rotate2D(MouvVec v1, double theta);                          // Return the rotate Pvector.
        static double angleWith(MouvVec ref_pos, MouvVec target, double theta);   	// Return the angle between the current PVector and another one.


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

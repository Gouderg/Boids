#include "../include/mouvVec.h"

MouvVec::MouvVec(const double x, const double y, const double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


void MouvVec::addVec(MouvVec v) {
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();
}

void MouvVec::subVec(MouvVec v) {
	this->x -= v.getX();
	this->y -= v.getY();
	this->z -= v.getZ();
}

void MouvVec::divVec(MouvVec v) {
	this->x /= v.getX();
	this->y /= v.getY();
	this->z /= v.getZ();	
}

void MouvVec::mulVec(MouvVec v) {
	this->x *= v.getX();
	this->y *= v.getY();
	this->z *= v.getZ();	
}

void MouvVec::addScal(double n) {
	this->x += n;
	this->y += n;
	this->z += n;
}

void MouvVec::subScal(double n) {
	this->x -= n;
	this->y -= n;
	this->z -= n;
}

void MouvVec::divScal(double n) {
	this->x /= n;
	this->y /= n;
	this->z /= n;	
}

void MouvVec::mulScal(double n) {
	this->x *= n;
	this->y *= n;
	this->z *= n;	
}

double MouvVec::magnitude() {
	return sqrt(pow(this->x,2) + pow(this->y, 2));
	// return sqrt(pow(this->x,2) + pow(this->y, 2) + pow(this->z, 2));

}

double MouvVec::dist(MouvVec v1, MouvVec v2) {
	return sqrt(pow(v1.getX() - v2.getX(),2) + pow(v1.getY() - v2.getY(),2));
	// return sqrt(pow(v1.getX() - v2.getX(),2) + pow(v1.getY() - v2.getY(),2) +  pow(v1.getZ() - v2.getZ(),2)); 
}

void MouvVec::normalize() {
	double mag = this->magnitude();

	if (mag > 0) {
		this->setX(this->x / mag);
		this->setY(this->y / mag);
		//this->setZ(this->z / mag);
	}
}
#include "mouvVec.h"

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
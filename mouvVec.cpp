#include "mouvVec.h"

MouvVec::MouvVec(const int x, const int y, const int z) {
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

void MouvVec::addScal(int n) {
	this->x += n;
	this->y += n;
	this->z += n;
}

void MouvVec::subScal(int n) {
	this->x -= n;
	this->y -= n;
	this->z -= n;
}

void MouvVec::divScal(int n) {
	this->x /= n;
	this->y /= n;
	this->z /= n;	
}

void MouvVec::mulScal(int n) {
	this->x *= n;
	this->y *= n;
	this->z *= n;	
}
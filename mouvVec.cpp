#include "mouvVec.h"

MouvVec::MouvVec(const int x, const int y, const int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

MouvVec::~MouvVec() {
	// std::cout << "Appel du destructeur MouvVec" << std::endl;
}


void MouvVec::addVec(MouvVec v) {

	this->x = this->x + v.getX();
	this->y = this->y + v.getY();
	this->z += v.getZ();
}


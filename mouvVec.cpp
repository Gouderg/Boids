#include "mouvVec.h"

MouvVec::MouvVec(const int x, const int y, const int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

MouvVec::~MouvVec() {
	std::cout << "Appel du destructeur" << std::endl;
}

void MouvVec::setPosition(const int x, const int y, const int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


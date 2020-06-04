#include "bird.h"

Bird::Bird(int id, int r, int g, int b) {
	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
}


Bird::~Bird() {
	//std::cout << "Appel du destructeur de bird" << std::endl;
}
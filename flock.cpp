#include "flock.h"

Flock::Flock() {

	for (int i = 0; i < nbBird; ++i) {
		Bird *bird = new Bird(i, rand()%255, rand()%255, rand()%255, SIZE_W/2, SIZE_H/2, SIZE_D/2);
		birds.push_back(bird);
	}

}

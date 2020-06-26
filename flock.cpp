#include "flock.h"

Flock::Flock() {

	for (int i = 0; i < nbBird; ++i) {
		Bird *bird = new Bird(i, rand()%255, rand()%255, rand()%255, rand()%SIZE_W, rand()%SIZE_H, rand()%SIZE_D);
		// Bird *bird = new Bird(i, rand()%255, rand()%255, rand()%255, SIZE_W/2, SIZE_H/2, SIZE_D);
		birds.push_back(bird);
	}

}

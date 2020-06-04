#include "flock.h"

Flock::Flock() {
	
	srand(time(NULL));
	bool isHere = false;
	int collision = 0;

	for (int i = 0; i < nbBird; ++i) {

		// Rentrer dans un while
		do {
			isHere = false;
			// Générer une valeur de x et une valeur de y
			int x = rand() % SIZE_W;
			int y = rand() % SIZE_H;

			// On parcours chaque bird déjà créé
			for (auto elt : birds) {
				// On regarde l'encadrement
				if ((x < elt.getX()+sizeBird && x > elt.getX()-sizeBird) || (y < elt.getY()+sizeBird && y > elt.getY()-sizeBird)) {
					isHere = true;
					collision ++;
				}
			}

			// Si tout est bon, on créer un nouvelle oiseau
			if (!isHere) {
				Bird bird = Bird(i, rand()%255, rand()%255, rand()%255);
				bird.setX(x);
				bird.setY(y);
				birds.push_back(bird);
			}

		// Sinon on recommence
		} while (isHere);
	}
	std::cout << "Nombre de collision: " << collision << std::endl;
}

Flock::~Flock() {
	//std::cout << "Appel du destructeur de Flock" << std::endl;
}

void Flock::display() {
	for (auto elt : birds) {
		std::cout << elt.getId() << std::endl;
	}
}
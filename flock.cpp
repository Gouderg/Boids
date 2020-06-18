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
			// int x = rand() % SIZE_W;
			// int y = rand() % SIZE_H;
			// int z = 0;

			// // On parcours chaque bird déjà créé
			// for (auto elt : birds) {
			// 	// On regarde l'encadrement
			// 	if ((x < elt->getPosition()->getX()+sizeBird && 
			// 		 x > elt->getPosition()->getX()-sizeBird) || 
			// 		(y < elt->getPosition()->getY()+sizeBird && 
			// 		 y > elt->getPosition()->getY()-sizeBird)) {
			// 		isHere = true;
			// 		collision ++;
			// 	}
			// }

			// Si tout est bon, on créer un nouvel oiseau
			if (!isHere) {
				Bird *bird = new Bird(i, rand()%255, rand()%255, rand()%255, 400, 300, 0);
				//Bird *bird = new Bird(i, rand()%255, rand()%255, rand()%255, x, y, z);
				birds.push_back(bird);
			}
		// Sinon on recommence
		} while (isHere);
	}
	std::cout << "Nombre de collision: " << collision << std::endl;
}

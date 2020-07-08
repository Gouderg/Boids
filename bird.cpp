#include "bird.h"

// Constructeur 
Bird::Bird(int id, int r, int g, int b, double xPos, double yPos, double zPos) {

	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	this->position = new MouvVec(xPos, yPos, zPos);
	this->velocite = new MouvVec(((rand() % 4000) - 1500)/1000.0, ((rand() % 4000) - 1500)/1000.0, 0);	
}

// Dessine la nouvelle position de l'oiseau
void Bird::drawBird(sf::RenderWindow *window, int sizeBird, int id) {
	
	double angle = M_PI - atan2(velocite->getX(),velocite->getY());

	// Oiseau
	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(position->getX() + (-sizeBird) * cos(angle) + (-sizeBird) * sin(angle), position->getY() + (-sizeBird) * sin(angle) + sizeBird * cos(angle)));
	convex.setPoint(1, sf::Vector2f(position->getX(), position->getY()));
	convex.setPoint(2, sf::Vector2f(position->getX() + (sizeBird) * cos(angle) + (-sizeBird) * sin(angle), position->getY() + sizeBird * sin(angle) + (sizeBird) * cos(angle)));
	convex.setPoint(3, sf::Vector2f(position->getX() + (sizeBird) * sin(angle), position->getY() + (-sizeBird) * cos(angle)));
	convex.setFillColor(sf::Color(getR(), getG(), getB()));
	window->draw(convex);

	/*if (id == 4) {
		sf::CircleShape circle(sizeBird * 12);
		circle.setPosition(position->getX() - sizeBird * 12, position->getY() - sizeBird * 12);
		circle.setFillColor(sf::Color(253, 241, 184, 50));
		window->draw(circle);
	}*/
	
	
}

// Update la position de l'oiseau en fonction des règles
void Bird::update(Flock nuee) {
	
	// Règle 1: cohésion
	this->velocite->addVec(cohesion(*this->position, nuee, this->id));
	// Règle 2: séparation
	this->velocite->addVec(separation(*this->position, nuee, this->id));
	// Règle 3: alignement
	this->velocite->addVec(alignement(*this->velocite, *this->position, nuee, this->id));
	
	// On ajuste la vitesse par rapport à la vitesse max
	limitVelocite(this->velocite, nuee.getVitesseMax());

	// On ajoute la vitesse à la position
	this->position->addVec(*this->velocite);
	checkEdges(nuee);
}

// Limite la vélocité maximale
void Bird::limitVelocite(MouvVec* velocite, double vitesseMax) {

	// On récupère la norme de la velocité
	double norme = velocite->normalize();
	
	// On divise le vecteur par sa norme
	velocite->divScal(norme);

	// On le multiplie par la vitesse
	velocite->mulScal(vitesseMax);
}

// Check les bordures de la map
void Bird::checkEdges(Flock nuee) {

	if (this->position->getX() > nuee.SIZE_W) this->position->setX(std::fmod(this->position->getX(), nuee.SIZE_W));
	if (this->position->getY() > nuee.SIZE_H) this->position->setY(std::fmod(this->position->getY(), nuee.SIZE_H));
	if (this->position->getZ() > nuee.SIZE_D) this->position->setZ(std::fmod(this->position->getZ(), nuee.SIZE_D));

	if (this->position->getX() < 0) this->position->setX(this->position->getX() + nuee.SIZE_W - this->position->getX());
	if (this->position->getY() < 0) this->position->setY(this->position->getY() + nuee.SIZE_H - this->position->getY());	
	if (this->position->getZ() < 0) this->position->setZ(this->position->getZ() + nuee.SIZE_D - this->position->getZ());	
}

// Règle 1: Cohésion (Calcule le centre perçu par les oiseaux afin de les attiré au même endroit) 
MouvVec Bird::cohesion(MouvVec position, Flock nuee, int id) {

	MouvVec perceivedCentre(0,0,0);
	int nbNeighbour = 0;

	for (auto bird : nuee.getBirds()) {
		MouvVec birdPosTemp(bird->position->getX(), bird->position->getY(), 0);
		if (bird->getId() != id) {
			if (std::abs(birdPosTemp.normalize() - position.normalize()) <= nuee.getZoneAttraction()) {
				perceivedCentre.addVec(birdPosTemp);		// On cumule chaque coordonnées
				nbNeighbour ++;	
			}
		}
	}
	if (nbNeighbour > 0) {
		perceivedCentre.divScal(nbNeighbour);				 		
		perceivedCentre.subVec(position);						
		perceivedCentre.mulScal(nuee.getAttraction());
		perceivedCentre.divScal(perceivedCentre.normalize());
	}

	return perceivedCentre;
}

// Règle 2: Séparation (Repousse les oiseaux qui sont autour)
MouvVec Bird::separation(MouvVec position, Flock nuee, int id) {
	MouvVec collision(0,0,0);
	int nbNeighbour = 0;

	for (auto bird: nuee.getBirds()) {
		if (bird->getId() != id) {
			MouvVec birdPosTemp(bird->position->getX(), bird->position->getY(), 0);
			if (std::abs(birdPosTemp.normalize() - position.normalize()) <= nuee.getZoneRepulsion()) {
				birdPosTemp.subVec(position); 	
				collision.subVec(birdPosTemp);
				nbNeighbour ++;
			}
		}
	}
	if (nbNeighbour > 0) collision.divScal(collision.normalize());

	return collision;
}

// Règle 3: S'aligner à la vitesse des autres oiseaux
MouvVec Bird::alignement(MouvVec velocite, MouvVec position, Flock nuee, int id) {
	MouvVec perceivedVelocity(0,0,0);
	int nbNeighbour = 0;

	for (auto bird: nuee.getBirds()) {
		if (bird->getId() != id) {
			MouvVec birdPosTemp(bird->position->getX(), bird->position->getY(), 0);
			if (std::abs(birdPosTemp.normalize() - position.normalize()) <= nuee.getZoneAlignement()) {
				perceivedVelocity.addVec(birdPosTemp);
				nbNeighbour ++;
			}
		}
	}

	if (nbNeighbour > 0) {
		perceivedVelocity.divScal(nbNeighbour);
		perceivedVelocity.subVec(velocite);
		perceivedVelocity.divScal(nuee.getAlignement());
	}
	return perceivedVelocity;
}

// Compte le nombre de voisins
void Bird::countNeighbours(Flock nuee, MouvVec position, int id) {
	if (id == 4) {
		int neighbour = 0;
		for (auto elt : nuee.getBirds()) {
			if (elt->getId() != id) {

				MouvVec* temp = new MouvVec(elt->position->getX(), elt->position->getY() , 0);
				MouvVec v = position;
				temp->subVec(v);
				double tempNorme = temp->normalize();
				if ( tempNorme < (nuee.getSizeBird() * 2)) {
					neighbour ++;
				}
				
			}
		}
		std::cout << neighbour << std::endl;
	}
}
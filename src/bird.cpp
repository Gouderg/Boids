#include "../include/bird.h"

Bird::Bird(int id, int r, int g, int b, double x, double y, double z) {

	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	this->position = new MouvVec(x, y, z);
	this->velocity = new MouvVec(((rand() % 4000) - 1500)/1000.0, ((rand() % 4000) - 1500)/1000.0, 0);
}

// Draw new bird
void Bird::drawBird(sf::RenderWindow *window, int sizeBird, int id) {
	
	// Bird
	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(-sizeBird , -sizeBird));
	convex.setPoint(1, sf::Vector2f(sizeBird , 0));
	convex.setPoint(2, sf::Vector2f(-sizeBird , sizeBird));
	convex.setPoint(3, sf::Vector2f(-sizeBird/2, 0));
	
	convex.setPosition(position->getX(), position->getY());
	convex.setRotation(velocity->headings());
	convex.setFillColor(sf::Color(getR(), getG(), getB()));
	window->draw(convex);

	if (id == 4) {
		sf::CircleShape circle(sizeBird * 2);
		circle.setPosition(position->getX() - sizeBird * 2, position->getY() - sizeBird * 2);
		circle.setFillColor(sf::Color(253, 241, 184, 50));
		window->draw(circle);
	}
	
	
}

// Update bird position with rules
void Bird::update(Flock nuee) {
	
	// Rule 1: cohesion
	this->velocity->addVec(cohesion(*this->position, nuee, this->id));
	// Rule 2: sparation
	this->velocity->addVec(separation(*this->velocity, *this->position, nuee, this->id));
	// Rule 3: alignment
	this->velocity->addVec(alignment(*this->velocity, *this->position, nuee, this->id));
	
	//countNeighbours(nuee, *this->position, this->id);
	// Adjust speed
	limit(this->velocity, nuee.getSpeedMax());

	this->position->addVec(*this->velocity);
	checkEdges(nuee);
}

// Limit vector with scalar
void Bird::limit(MouvVec* vecteur, double valMax) {

	if (std::abs(vecteur->magnitude()) > valMax) {
		vecteur->normalize();
		vecteur->mulScal(valMax);
	}
	
}

// Check map borders
void Bird::checkEdges(Flock nuee) {

	// 2-tore 
	if (this->position->getX() > nuee.SIZE_W) this->position->setX(std::fmod(this->position->getX(), nuee.SIZE_W));
	if (this->position->getY() > nuee.SIZE_H) this->position->setY(std::fmod(this->position->getY(), nuee.SIZE_H));
	if (this->position->getZ() > nuee.SIZE_D) this->position->setZ(std::fmod(this->position->getZ(), nuee.SIZE_D));

	if (this->position->getX() < 0) this->position->setX(nuee.SIZE_W);
	if (this->position->getY() < 0) this->position->setY(nuee.SIZE_H);	
	if (this->position->getZ() < 0) this->position->setZ(nuee.SIZE_D);	

}

// Rule 1: Cohesion (Calculate the perceived center with his neighbours) 
MouvVec Bird::cohesion(MouvVec position, Flock nuee, int id) {

	MouvVec perceivedCentre(0,0,0);
	int nbNeighbour = 0;

	for (auto bird : nuee.getBirds()) {
		MouvVec birdPosTemp(bird->position->getX(), bird->position->getY(), 0);
		if (bird->getId() != id) {
			if (MouvVec::dist(position, *bird->position) <= nuee.getAttractionArea()) {
				perceivedCentre.addVec(birdPosTemp);		// On cumule chaque coordonnées
				nbNeighbour ++;	
			}
		}
	}
	if (nbNeighbour > 0) {
		perceivedCentre.divScal(nbNeighbour);				 		
		perceivedCentre.subVec(position);						
		perceivedCentre.mulScal(nuee.getAttraction());
		limit(&perceivedCentre, nuee.getForceMax());
	}

	return perceivedCentre;
}

// Rule 2: Separation (Repels birds around)
MouvVec Bird::separation(MouvVec velocity, MouvVec position, Flock nuee, int id) {
	MouvVec collision(0,0,0);
	int nbNeighbour = 0;

	for (auto bird: nuee.getBirds()) {
		if (bird->getId() != id) {
			MouvVec birdPosTemp(bird->position->getX(), bird->position->getY(), 0);
			if (MouvVec::dist(position, *bird->position) <= nuee.getRepulsionArea()) {
				birdPosTemp.subVec(position);
				birdPosTemp.divScal(pow(MouvVec::dist(position, *bird->position),2));
				collision.addVec(birdPosTemp);
				nbNeighbour ++;
			}
		}
	}
	if (nbNeighbour > 0) {
		collision.divScal(nbNeighbour);
		collision.normalize();
		collision.mulScal(nuee.getSpeedMax());
		collision.subVec(velocity);
		limit(&collision, nuee.getForceMax());
	}

	collision.mulScal(nuee.getRepulsion());
	return collision;
}

// Rule 3: Alignment of speed bird
MouvVec Bird::alignment(MouvVec velocity, MouvVec position, Flock nuee, int id) {
	MouvVec perceivedVelocity(0,0,0);
	int nbNeighbour = 0;

	for (auto bird: nuee.getBirds()) {
		if (bird->getId() != id) {
			MouvVec birdPosTemp(bird->position->getX(), bird->position->getY(), 0);
			if (MouvVec::dist(position, *bird->position) <= nuee.getAlignmentArea()) {
				perceivedVelocity.addVec(birdPosTemp);
				nbNeighbour ++;
			}
		}
	}

	if (nbNeighbour > 0) {
		perceivedVelocity.divScal(nbNeighbour);
		perceivedVelocity.subVec(velocity);
		perceivedVelocity.divScal(nuee.getAlignment());
		limit(&perceivedVelocity, nuee.getForceMax());
	}
	return perceivedVelocity;
}

// Count neighbours
void Bird::countNeighbours(Flock nuee, MouvVec position, int id) {
	if (id == 4) {
		int neighbour = 0;
		for (auto elt : nuee.getBirds()) {
			if (elt->getId() != id) {

				MouvVec* temp = new MouvVec(elt->position->getX(), elt->position->getY() , 0);
				MouvVec v = position;
				temp->subVec(v);
				double tempNorme = temp->magnitude();
				if ( tempNorme < (nuee.getSizeBird() * 2)) {
					neighbour ++;
				}
			}
		}
		std::cout << neighbour << std::endl;
	}
}
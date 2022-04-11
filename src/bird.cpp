#include "../include/bird.h"

Bird::Bird(int id, int r, int g, int b, double x, double y, double z) {

	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	if (id == 1) {
		this->position = new MouvVec(x, y, z);
	} else {
		this->position = new MouvVec(x, y - 30, z);
	}
	// this->velocity = new MouvVec(((rand() % 4000) - 1500)/1000.0, ((rand() % 4000) - 1500)/1000.0, 0);
	this->velocity = new MouvVec(-1,1,0);
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

	if (id == 1) {
		sf::CircleShape circle(sizeBird * 12);
		circle.setPosition(position->getX() - sizeBird * 12, position->getY() - sizeBird * 12);
		circle.setFillColor(sf::Color(253, 241, 184, 50));
		window->draw(circle);
	}	
	
}

// Update bird position with rules
void Bird::update(Flock nuee) {

	
	MouvVec acc = MouvVec((rand() % 20 - 10.0) / 100.0, (rand() % 20 - 10.0) / 100.0, 0);	
	if (this->id == 1) {
		countNeighbours(nuee, *this->position, *this->velocity, this->id);
	}
	// Add acceleration.
	this->velocity->add(acc);

	// Adjust speed
	this->velocity->limit(nuee.getSpeedMax());

	this->position->add(*this->velocity);
	
	// Rule 1: cohesion
	// acc.addVec(seek(nuee, cohesion(*this->position, nuee, this->id)));
	// Rule 2: separation
	// acc.addVec(flee(nuee, separation(*this->velocity, *this->position, nuee, this->id)));
	// Rule 3: alignment
	// acc.addVec(seek(nuee, alignment(*this->velocity, *this->position, nuee, this->id)));
	
	checkEdges(nuee);
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
				perceivedCentre.add(birdPosTemp);		// On cumule chaque coordonnées
				nbNeighbour ++;	
			}
		}
	}
	if (nbNeighbour > 0) {
		perceivedCentre.div(nbNeighbour);				 		
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
				birdPosTemp.sub(position);
				birdPosTemp.div(pow(MouvVec::dist(position, *bird->position),2));
				collision.add(birdPosTemp);
				nbNeighbour ++;
			}
		}
	}
	if (nbNeighbour > 0) {
		collision.div(nbNeighbour);
		collision.normalize();
		collision.mul(nuee.getSpeedMax());
		collision.sub(velocity);
		collision.limit(nuee.getForceMax());
	}

	collision.mul(nuee.getRepulsion());
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
				perceivedVelocity.add(birdPosTemp);
				nbNeighbour ++;
			}
		}
	}

	if (nbNeighbour > 0) {
		perceivedVelocity.div(nbNeighbour);
		perceivedVelocity.sub(velocity);
		perceivedVelocity.div(nuee.getAlignment());
		perceivedVelocity.limit(nuee.getForceMax());
	}
	return perceivedVelocity;
}

// Count neighbours
void Bird::countNeighbours(Flock nuee, MouvVec position, MouvVec velocity, int id) {

	int neighbour = 0;
	for (auto elt : nuee.getBirds()) {
		if (elt->getId() != id && MouvVec::dist(*elt->position, position) < (nuee.getAttractionArea()) && MouvVec::angleWith(position, *elt->position, velocity.headings()) <= 150 ) {
			neighbour ++;
		}
	}
	std::cout << neighbour << std::endl;
}

// Go to a point.
MouvVec Bird::seek(Flock nuee, MouvVec target) {
    target.sub(*this->getPosition());
    target.setMag(nuee.getSpeedMax());
    target.sub(*this->getVelocity());
    target.limit(nuee.getForceMax());
    return target;
}

MouvVec Bird::flee(Flock nuee, MouvVec target) {
	MouvVec force = this->seek(nuee, target);
    force.mul(-1);
    return force;
}
#include "bird.h"

// Constructeur 
Bird::Bird(int id, int r, int g, int b, int xPos, int yPos, int zPos) {

	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	this->position = new MouvVec(xPos, yPos, zPos);
	//this->velocite = new MouvVec((rand() % 20) - 10, (rand() % 20) - 10, 0);
	this->velocite = new MouvVec((rand() % 12) - 6, (rand() % 12) - 6, 0);
	


	int xB = xPos + this->velocite->getX();
	int yB = yPos;
	int xC = xPos + this->velocite->getX();
	int yC = yPos + this->velocite->getY();

	this->angle = static_cast<int>(atan((sqrt(pow(xC - xB,2) + pow(yC - yB,2))) / (sqrt(pow(xB - xPos,2) + pow(yB - yPos,2)))) * 180/M_PI);
	
}

// Dessine la nouvelle position de l'oiseau
void Bird::drawBird(sf::RenderWindow *window, int sizeBird) {

	// Oiseau
	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(position->getX(), position->getY()));
	convex.setPoint(1, sf::Vector2f(position->getX() - sizeBird, position->getY() + sizeBird));
	convex.setPoint(2, sf::Vector2f(position->getX(), position->getY() - sizeBird));
	convex.setPoint(3, sf::Vector2f(position->getX() + sizeBird, position->getY() + sizeBird));
	convex.setFillColor(sf::Color(getR(), getG(), getB()));
	//convex.setRotation(getAngle());
	window->draw(convex);

	// // Zone de collision de l'oiseau
	// sf::CircleShape circle(sizeBird * 4);
	// circle.setPosition(position->getX() - sizeBird * 4, position->getY() - sizeBird * 4);
	// circle.setFillColor(sf::Color(253, 241, 184, 50));
	// window->draw(circle);

}

// Update la position de l'oiseau en fonction des règles
void Bird::update(Flock nuee) {
	
	// Règle 1: cohésion
	//this->velocite->addVec(cohesion(*this->position, nuee, this->id));
	// Règle 2: séparation
	// Règle 3: alignement

	std::cout << this->velocite->getX() << " : " << this->velocite->getY() << std::endl;
	this->position->addVec(*this->velocite);

	// Regarde si les oiseaux sortent du cadre ou non
	if (this->position->getX() > nuee.SIZE_W) this->position->setX(this->position->getX() % nuee.SIZE_W);
	if (this->position->getY() > nuee.SIZE_H) this->position->setY(this->position->getY() % nuee.SIZE_H);
	if (this->position->getZ() > nuee.SIZE_D) this->position->setZ(this->position->getZ() % nuee.SIZE_D);

	if (this->position->getX() < 0) this->position->setX(this->position->getX() + nuee.SIZE_W - this->position->getX());
	if (this->position->getY() < 0) this->position->setY(this->position->getY() + nuee.SIZE_H - this->position->getY());	
	if (this->position->getZ() < 0) this->position->setZ(this->position->getY() + nuee.SIZE_D - this->position->getZ());	
}

// Rule 1: Cohesion (Calcule le centre perçu par les oiseaux) 
MouvVec Bird::cohesion(MouvVec position, Flock nuee, int id) {

	MouvVec allCentre;

	for(auto bird : nuee.getBirds()) {
		if (bird->getId() != id) {
			allCentre.addVec(*bird->position);		// On cumule chaque coordonnées 
		}
	}

	allCentre.divScal(nuee.getNbBird() - 1); 		// On divise par le nombre d'oiseau comptabilisé
	allCentre.subVec(position);						// On retire les coordonées de l'oiseau en question
	allCentre.divScal(100);							// à remplacer
	
	return allCentre;
}
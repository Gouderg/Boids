#include "bird.h"

// Constructeur 
Bird::Bird(int id, int r, int g, int b, int angle, int xPos, int yPos, int zPos) {

	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	this->angle = angle;
	this->position = new MouvVec(xPos, yPos, zPos);
	this->vitesse = new MouvVec((rand() % 12) - 6, (rand() % 12) - 6, 0);

}


void Bird::drawBird(sf::RenderWindow *window, int sizeBird) {

	// Oiseau
	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(position->getX(), position->getY()));
	convex.setPoint(1, sf::Vector2f(position->getX() - sizeBird, position->getY() + sizeBird));
	convex.setPoint(2, sf::Vector2f(position->getX(), position->getY() - sizeBird));
	convex.setPoint(3, sf::Vector2f(position->getX() + sizeBird, position->getY() + sizeBird));
	convex.setFillColor(sf::Color(getR(), getG(), getB()));
	window->draw(convex);

	// // Zone de collision de l'oiseau
	// sf::CircleShape circle(sizeBird * 4);
	// circle.setPosition(position->getX() - sizeBird * 4, position->getY() - sizeBird * 4);
	// circle.setFillColor(sf::Color(253, 241, 184, 50));
	// window->draw(circle);

}

void Bird::update(const int SIZE_W, const int SIZE_H, const int SIZE_D) {
	
	this->getPosition()->addVec(*this->getVitesse());

	// Regarde si les oiseaux sortent du cadre ou non
	if (this->getPosition()->getX() > SIZE_W) this->getPosition()->setX(this->getPosition()->getX() % SIZE_W);
	if (this->getPosition()->getY() > SIZE_H) this->getPosition()->setY(this->getPosition()->getY() % SIZE_H);
	if (this->getPosition()->getZ() > SIZE_D) this->getPosition()->setZ(this->getPosition()->getZ() % SIZE_D);

	if (this->getPosition()->getX() < 0) this->getPosition()->setX(this->getPosition()->getX() + SIZE_W - this->getPosition()->getX());
	if (this->getPosition()->getY() < 0) this->getPosition()->setY(this->getPosition()->getY() + SIZE_H - this->getPosition()->getY());	
	if (this->getPosition()->getZ() < 0) this->getPosition()->setZ(this->getPosition()->getY() + SIZE_D - this->getPosition()->getZ());	
}

Bird::~Bird() {
	//std::cout << "Appel du destructeur de bird" << std::endl;
}
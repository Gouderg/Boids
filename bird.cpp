#include "bird.h"

// Constructeur 
Bird::Bird(int id, int r, int g, int b, int angle, int x, int y, int z) {
	this->id = id;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	this->angle = angle;
	this->position = new MouvVec(x, y, z);
}


void Bird::drawBird(sf::RenderWindow *window, int sizeBird) {

	// sf::CircleShape triangle(sizeBird, 3);
	// triangle.setFillColor(sf::Color(getR(), getG(), getB()));
	// triangle.setPosition(getX(),getY());
	// triangle.setRotation(getAngle());
	// window->draw(triangle);

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(position->getX(), position->getY()));
	convex.setPoint(1, sf::Vector2f(position->getX() - sizeBird, position->getY() + sizeBird));
	convex.setPoint(2, sf::Vector2f(position->getX(), position->getY() - sizeBird));
	convex.setPoint(3, sf::Vector2f(position->getX() + sizeBird, position->getY() + sizeBird));
	convex.setFillColor(sf::Color(getR(), getG(), getB()));
	window->draw(convex);

	sf::CircleShape circle(sizeBird * 4);
	circle.setPosition(position->getX() - sizeBird * 4, position->getY() - sizeBird * 4);
	circle.setFillColor(sf::Color(253, 241, 184, 50));
	window->draw(circle);

}

Bird::~Bird() {
	//std::cout << "Appel du destructeur de bird" << std::endl;
}
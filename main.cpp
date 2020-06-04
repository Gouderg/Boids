#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include  <iostream>

#include "bird.h"
#include "flock.h"

int main(int argc, char const *argv[]) {	
	
	Flock nuee = Flock();
	nuee.display();

	// Initialisation de l'antialiasing et de la fenêtre
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(nuee.SIZE_W,nuee.SIZE_H), "Boids", sf::Style::Default, settings);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {							// Attente d'évènement
			if(event.type == sf::Event::Closed) window.close();		// Fermeture de la fenetre
		}
		// On nettoie notre écran
		window.clear(sf::Color(25,25,112,128));
		
		for (auto elt : nuee.getBirds()) {
			sf::CircleShape triangle(nuee.getSizeBird(), 3);
			triangle.setFillColor(sf::Color(elt.getR(), elt.getG(), elt.getB()));	
			triangle.setPosition(elt.getX(),elt.getY());
			window.draw(triangle);
		}
		
		window.display();
	}


	return 0;
}
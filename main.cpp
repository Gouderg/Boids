#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <unistd.h>
#include <ctime>

#include "bird.h"
#include "flock.h"
#include "mouvVec.h"

int main(int argc, char const *argv[]) {	
	
	srand(time(NULL));	

	// Initialisation d'une nuee
	Flock nuee = Flock();

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
		window.clear(sf::Color(25,25,100,80));
		
		// On parcours chaque oiseau
		for (auto elt : nuee.getBirds()) {
			elt->update(nuee);// On update la position de l'oiseau en fonction de sa vitesse
			elt->drawBird(&window, nuee.getSizeBird()); // On redessine la nouvelle postion de l'oiseau
		}
		
		window.display();

		usleep(10000); // 0.01 seconde

	}


	return 0;
}
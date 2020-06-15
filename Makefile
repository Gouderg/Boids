boid: main.o flock.o bird.o mouvVec.o
	g++ $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp flock.h
	g++ -Wall -std=c++11 -c $<

flock.o: flock.cpp flock.h
	g++ -Wall -std=c++11 -c $<

bird.o: bird.cpp bird.h
	g++ -Wall -std=c++11 -c $<

mouvVec.o: mouvVec.cpp mouvVec.h
	g++ -Wall -std=c++11 -c $<

clean:
	rm *.o boid

r: clean boid
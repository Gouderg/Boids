all: boid clean

boid: main.o flock.o bird.o mouvVec.o
	g++ $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp include/flock.h
	g++ -Wall -std=c++11 -c $<

flock.o: src/flock.cpp include/flock.h
	g++ -Wall -std=c++11 -c $<

bird.o: src/bird.cpp include/bird.h
	g++ -Wall -std=c++11 -c $<

mouvVec.o: src/mouvVec.cpp include/mouvVec.h
	g++ -Wall -std=c++11 -c $<

clean:
	rm *.o

r: clean boid
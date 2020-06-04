boid: main.o flock.o bird.o
	g++ $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp flock.h
	g++ -Wall -c $<

flock.o: flock.cpp flock.h
	g++ -Wall -c $<

bird.o: bird.cpp bird.h
	g++ -Wall -c $<

clean:
	rm *.o boid

r: clean boid
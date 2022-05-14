CC = g++

all: main

main: main.o Queue.hpp
	$(CC) -o main main.o -lpthread

#Queue: Queue.o
#	$(CC) -o Queue Queue.o

Queue.o: Queue.cpp Queue.hpp
	$(CC) -c Queue.cpp -lpthread

main.o: main.cpp Queue.hpp
	$(CC) -c main.cpp -lpthread


clean:
	rm -f *.o main Queue
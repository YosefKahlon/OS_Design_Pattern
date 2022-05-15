CC = g++

all: main

main: main.o queue.h
	$(CC) -o main main.o -lpthread

#Queue: Queue.o
#	$(CC) -o Queue Queue.o

queue.o: queue.c queue.h
	$(CC) -c Queue.cpp -lpthread

main.o: main.cpp queue.h
	$(CC) -c main.cpp -lpthread


clean:
	rm -f *.o main queue
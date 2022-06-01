CC = gcc
CZZ = g++
#OBJ=active_object.o guard.o reactor.o queue.o


all: main1 queue.o client singleton pollserver pollclient Reactor.o object_active.o library.so

main1: main1.o queue.h
	$(CC) -o main main1.o -lpthread

pollserver: pollserver.c Reactor.h
	$(CC) pollserver.c -o pollserver -lpthread

Reactor: Reactor.o
	$(CC) -o Reactor Reactor.o

queue: queue.o
	$(CC) -o queue queue.o

queue.o: queue.c queue.h
	$(CC) -c queue.c


main.o: main1.c queue.h
	$(CC) -c main1.c

client: client.c
	$(CC) client.c -o client

singleton: singleton.cpp Guard.cpp
	$(CZZ) -o singelton singelton.o -lpthread

pollclient: pollclient.o
	$(CC) pollclient.c -o pollclient


object_active.o: object_active.h object_active.c
	gcc -c object_active.c -lpthread -fPIC

Reactor.o: Reactor.c Reactor.h
	$(CC) -c Reactor.c

library.so: object_active.o guard.o reactor.o queue.o
	gcc --shared -fPIC -pthread  guard.o reactor.o queue.o object_active.o



guard.o: Guard.cpp
	g++ -c Guard.cpp -lpthread


clean:
	rm -f *.o main queue client pollclient pollserver
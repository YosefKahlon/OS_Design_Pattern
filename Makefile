CC = gcc
CZZ = g++
#OBJ=active_object.o guard.o reactor.o queue.o


all: main1 queue.o client singleton pollserver pollclient Reactor.o object_active.o singleton.o library.so

main1: main1.o queue.h
	$(CC) -o main main1.o -lpthread

pollserver: pollserver.c reactor.hpp
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

singleton.o: singleton.cpp
	$(CZZ) -c singleton.cpp

singleton: singleton.o guard.cpp
	$(CZZ) -o singelton singleton.o -lpthread



pollclient: pollclient.o
	$(CC) pollclient.c -o pollclient


object_active.o: object_active.h object_active.c
	gcc -c object_active.c -lpthread -fPIC

Reactor.o: reactor.cpp reactor.hpp
	$(CC) -c Reactor.cpp

library.so: object_active.o guard.o reactor.o queue.o
	gcc --shared -fPIC -pthread  guard.o reactor.o queue.o object_active.o



guard.o: guard.cpp
	g++ -c Guard.cpp -lpthread


clean:
	rm -f *.o main queue client pollclient pollserver
CC = gcc
CZZ = g++
#OBJ=active_object.o guard.o reactor.o queue.o


all: main1 queue.o client singleton pollserver pollclient library.so Reactor.o

main1: main1.o queue.h
	$(CC) -o main main1.o -lpthread

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

pollclient: poolclient.o
	$(CC) pollclient.c -o pollclient

#library.so: active_object.o guard.o reactor.o queue.o
#	gcc --shared -fPIC -pthread active_object.o guard.o reactor.o queue.o

pollclient: poolserver.o Reactor.h
	$(CC) pollserver.c -o pollserver -lpthread


clean:
	rm -f *.o main queue client pollclient pollserver
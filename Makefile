CC = gcc



all: main1 queue.o client

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

clean:
	rm -f *.o main queue client
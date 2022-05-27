CC = gcc



all: main1 queue.o

main1: main1.o queue.h
	$(CC) -o main main1.o -lpthread

queue: queue.o
	$(CC) -o queue queue.o

queue.o: queue.c queue.h
	$(CC) -c queue.c


main.o: main1.c queue.h
	$(CC) -c main1.c


clean:
	rm -f *.o main queue
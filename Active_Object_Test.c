//
// Created by barak on 02/06/2022.
//

//
// Created by 97252 on 4/14/2022.
//

/*
** client.c -- a stream socket client demo
*/


#define text_length 1024
#define EQUAL 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "assert.h"
#include "pthread.h"

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 100 // max number of bytes we can get at once


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

typedef struct arg_test {
    char text[1024];
    char expected[1024];
    int sock;
} *p_arg_test, arg_test;

void *test_thread(void *arg) {


    /** send the text given in the arg_test struct to the server */
    p_arg_test argument = (p_arg_test) arg;
    printf("Socket : %d stated TEST \n", argument->sock);
    ssize_t numb = send(argument->sock, argument->text, text_length, 0);
    if (numb == -1) {
        printf("Test Failed at connection || socket : %d\n", argument->sock);
        close(argument->sock);
    }
    char buf[1024];
    size_t numberb;
    /** receive the message from the server,
     *  check if the message is encrypted well, print a matching indication of the compare */
    if ((numberb = recv(argument->sock, buf, text_length, 0)) == -1) {
        printf("Test failed at -> recv || socket : %d\n", argument->sock);
//        exit(1);
        return NULL;
    } else {
        if(strcmp(buf, argument->expected) != 0) {
            printf("Test Failed at comparing || socket : %d\n", argument->sock);
            return NULL;
        }
        printf("Expected value : %s | Actual : %s \n",argument->expected, buf);
        printf("Socket : %d Passed the TEST\n", argument->sock);
    }
}

int main(int argc, char *argv[]) {
//    int desc = dup(1); // close stout
    int t1_sock, t2_sock, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((t1_sock = socket(p->ai_family, p->ai_socktype,
                              p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(t1_sock, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(t1_sock);
            continue;
        }

        if ((t2_sock = socket(p->ai_family, p->ai_socktype,
                              p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(t2_sock, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(t1_sock);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure


    /** open 2 threads for each client */
    pthread_t thread1;
    pthread_t thread2;
    /** init 2 arg_test struct and assign their values:
     *          sock -> each client sock
     *          text -> for send to server
     *          expected -> the encrypted message that should return from the server
     */
    arg_test t1_arg;
    arg_test t2_arg;

    t1_arg.sock = t1_sock;
    t2_arg.sock = t2_sock;
    strcpy(t1_arg.text, "HELLO");
    strcpy(t1_arg.expected, "ifmmp");

    strcpy(t2_arg.text, "GOODBYE");
    strcpy(t2_arg.expected, "hppeczf");

    /** exe the threads on the thread func , each with different arguments (sock, text, expected)*/
    pthread_create(&thread1, NULL, &test_thread, &t1_arg);
    pthread_create(&thread2, NULL, &test_thread, &t2_arg);

    /** wait for the threads return */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);



//    printf("All Tests PASSED!\n");
    close(t1_sock);
    close(t2_sock);

    return 0;
}
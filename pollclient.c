//
// Created by 97252 on 6/1/2022.
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

#include <arpa/inet.h>
#include <signal.h>

#define PORT "9034" // the port client will be connecting to

#define MAXDATASIZE 100 // max number of bytes we can get at once

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
//    int desc = dup(1); // close stout
    int c_sock, numbytes;
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
        if ((c_sock = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(c_sock, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(c_sock);
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


    // dup2(c_sock,1);
    while (1) {

        if (fork() != 0) {
            char *command = NULL;
            size_t size = 0;

            //s-size_t type to be able to receive value -1 // size of the input  line
            ssize_t line_size = getline(&command, &size, stdin);
            command[line_size - 1] = '\0';





            send(c_sock, command, text_length, 0);


        } else {
            char top[text_length];
            size_t numb;
            if ((numb = recv(c_sock, top, text_length, 0)) == -1) {
                perror("recv");
                if (numb == 0) {
//                    kill(getppid(),SIGKILL);
                    break;
                }

                exit(1);
            }


            top[numb] = '\0';
            printf("%s \n", top);


        }
    }
    printf("closed connection\n");
    close(c_sock);

    return 0;
}
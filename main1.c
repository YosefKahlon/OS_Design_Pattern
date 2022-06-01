


#include <stdio.h>
#include "queue.h"
#include "string.h"
#include "queue.c"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "object_active.c"
//#include "Guard.cpp"
#define text_length 1024
#define EQUAL 0


#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


//#include "queue.h"
//#include "queue.c"
#include "assert.h"


#define PORT "3490"

#define BACKLOG 10     // how many pending connections queue will hold
int server_running = 1;
int sockfd;
int new_fd[BACKLOG];

Queue *first_q;
Queue *second_q;
Queue *third_q;

void *encrypt(void *data) {
    node *pack = (node *) data;

    printf("encrypting data --> %s \n",(char *)pack->data);
    char str[1024];// = (char *) data;
    strcpy(str, (char *) data);
//    printf("%s ,str \n", str);
    char ch;
    int key = 1;
    for (int i = 0; str[i] != '\0'; ++i) {
        ch = str[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch + key;
            if (ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }
            str[i] = ch;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = ch + key;
            if (ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }
            str[i] = ch;
        }
    }

//    pack->data = str;
    strcpy(pack->data, str);

    printf("\n\n");
    return pack;
}

void pass_to_second(void *data) {
    node *pass = (node *) data;
    char *text = pass->data;
    printf("passing to second QUEUE the value %s \n", text);
    enQ(&second_q, text, pass->fd);
    printf("\n\n");
}

void *upper_lower(void *data) {
    node *pack = (node *) data;
    printf("Transformin letters --> %s\n", (char*) data);
    char message[1024];
    strcpy(message, (char *) pack->data);
    int i = 0;
    while (message[i] != '\0') {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = tolower(message[i]);
        } else if (message[i] >= 'a' && message[i] <= 'z') {

            message[i] = toupper(message[i]);
        } else {
            printf("Bad input \n");
            exit(0);

        }
        i++;
    }

//    pack->data = message;
    strcpy(pack->data, message);
    printf("\n\n");
    return pack;


}

void pass_to_third(void *data) {
    node *pass = (node *) data;
    char *text = pass->data;
    printf("passing to third QUEUE the value %s \n", text);
    enQ(&third_q, text, pass->fd);
    printf("\n\n");

}


void *validation(void *data) {
    printf("Passed the packet %s\n", (char *) data);
    return NULL;
}

void *send_to_client(void *data) {

    node *send_n = (node *) data;

    if (send(send_n->fd, send_n->data, strlen(send_n->data), 0) == -1) { perror("Send"); }
//    validation(data);
    return data;
}

///////////////////////////////////////////////////

void sig_handler(int signum) {
    server_running = 0;
    for (int i = 1; i < BACKLOG; ++i) {
        close(new_fd[i]);
    }
    close(sockfd);


    exit(1);
}

void sigchld_handler(int s) {
    (void) s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

void *send_hello(void *arg) {
    int *s = (int *) arg;
    if (send(*s, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    return 0;
}


void *server_listener(void *arg) {
    pthread_detach(pthread_self());
    int *s = (int *) arg;
//    if (send(*s, "Hello, world!", 13, 0) == -1) {
//        perror("send");
//    }
    char client_msg[text_length] = {0}; // '\0'

    while (1) {
        memset(client_msg, 0, text_length);
        size_t r;
        if ((r = recv(*s, client_msg, sizeof(client_msg), 0)) == -1) {
            perror("recv");
            exit(1);
        }
        if (r != 0) {
            printf("%s --> \n", client_msg);


            enQ(&first_q,client_msg, *s);


        } else {
            break;
        }
    }
}


int main() {
    first_q = createQ();
    second_q = createQ();
    third_q = createQ();
    active_object *activeObject_encrypt;
    active_object *activeObject_UPPER_LOWER;
    active_object *activeObject_return_to_client;

    activeObject_encrypt = newAO(first_q, encrypt, pass_to_second);
    activeObject_UPPER_LOWER = newAO(second_q, upper_lower, pass_to_third);
    activeObject_return_to_client = newAO(third_q, send_to_client, validation);





    //------------------------------------ server -----------------------------------------------

    int status;

    /* Connection methods start here -> */
    // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        printf(" hello from PID: %d\n", getpid());
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    signal(SIGINT, sig_handler);

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    /* initializing array of threads with size of 10(the max of concurrency clients).
     * also init unsigned long thread_num to be the index of each thread
     * that will serve the current connection with the client*/
    pthread_t client_h[BACKLOG];
    unsigned long thread_num = 1;


    while (server_running) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd[thread_num] = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (new_fd[thread_num] == -1) {
            perror("accept");
            continue;
        }


        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *) &their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        /* in case we had more that 10 clients total(not at the same time) we can go point back to the previous threads
         * by module the curr index with backlog.*/
        thread_num %= BACKLOG;
        printf("SOCK NUM : %d\n", new_fd[thread_num]);
        /*create new executable thread to handle the connection with the client (to reply hello world...)*/

        pthread_create(&client_h[thread_num], NULL, &server_listener, &new_fd[thread_num]);
        /* increasing the counter for next pthread in the queue*/
        thread_num++;
    }
//    free_stack(&shared_st);




    wait(&status);
//    close(new_fd);

    return 0;
}

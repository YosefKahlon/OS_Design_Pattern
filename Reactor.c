//
// Created by barak on 01/06/2022.
//

#include "Reactor.h"
#include "stdlib.h"


void * newReactor() {
    reactor *re = (reactor *)malloc(sizeof (reactor));

    return re;
}

void InstallHandler(reactor * rexi, void *func , int fd) {
    rexi->fd = fd;
    pthread_create(&rexi->re_thread, NULL, func, &fd);

}

void RemoveHandler(reactor * rexi) {
    pthread_cancel(rexi->re_thread);
    free(rexi);

}

void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    if (*fd_count == *fd_size) {
        *fd_size *= 2; // Double it

        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}

// Remove an index from the set
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count-1];

    (*fd_count)--;
}
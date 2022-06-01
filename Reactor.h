//
// Created by 97252 on 6/1/2022.
//

#ifndef OS_DESIGN_PATTERN_REACTOR_H
#define OS_DESIGN_PATTERN_REACTOR_H

#include "poll.h"
#include "pthread.h"

typedef struct Reactor {
    int fd;
    pthread_t re_thread;

} reactor;

void *newReactor();

void InstallHandler(reactor *rexi, void *func, int fd);

void RemoveHandler();

void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);


#endif //OS_DESIGN_PATTERN_REACTOR_H

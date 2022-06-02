//
// Created by 97252 on 6/1/2022.
//

#ifndef OS_DESIGN_PATTERN_REACTOR_HPP
#define OS_DESIGN_PATTERN_REACTOR_HPP

#include "poll.h"
#include "pthread.h"

typedef struct reactor {
    int fd;
    pthread_t re_thread;
    void *(*func)(void *);

} reactor;

void *newReactor();

void InstallHandler(reactor *rexi, void *(*func)(void *), int fd);

void RemoveHandler();



#endif //OS_DESIGN_PATTERN_REACTOR_HPP

//
// Created by barak on 01/06/2022.
//

#include "reactor.hpp"
#include "stdlib.h"


void * newReactor() {
    reactor *re = (reactor *)malloc(sizeof (reactor));

    return re;
}

void InstallHandler(reactor * rexi, void *(*func)(void *) , int fd) {

    rexi->fd = fd;
    rexi->func = func;
    pthread_create(&rexi->re_thread, NULL, rexi->func, (void *)rexi);

}

void RemoveHandler(reactor * rexi) {
    pthread_cancel(rexi->re_thread);
    free(rexi);

}
//
// Created by 97252 on 5/27/2022.
//
#include "pthread.h"
#include "unistd.h"
#include "object_active.h"
#include "stdlib.h"


void * EXE(void * arg){
    active_object *activeObject = (active_object*) arg;
    while (activeObject->status == Running) {
        void *data = activeObject->f1(deQ(&activeObject->queue));
        activeObject->f2(data);
    }
    return NULL;
}

active_object *newAO(Queue *queue, void *f1, void *f2) {
    active_object *active_o = (active_object *) malloc(sizeof(active_object));
    active_o->queue = queue;
    active_o->f1 = f1;
    active_o->f2 = f2;
    active_o->status = Running;
    active_o->thread = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_create(active_o->thread, NULL, &EXE, (void *) active_o);
    return active_o;
}


void *destroyAO(active_object *ao) {
    free(ao->thread);
    free(ao);

}
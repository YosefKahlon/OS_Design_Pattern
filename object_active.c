//
// Created by 97252 on 5/27/2022.
//

#include "object_active.h"
#include "stdlib.h"

void *run(void *);

active_object * newAO(Queue* queue, void * f1, void *f2){
    active_object  *ao = (active_object*) malloc(sizeof (active_object));
    ao->queue = queue;
   ao->f1 = f1;
   ao->f2 = f2;
    ao->thread = (pthread_t*) malloc(sizeof (pthread_t));
    pthread_create(ao->thread,NULL,&run,(void *)ao);
    return ao;



}

void *run(void * arg ) {

    active_object * active = (active_object*)arg;
    



}

void* destroyAO(active_object* ao ){
    free(ao->thread);
    free(ao);

}
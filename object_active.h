//
// Created by 97252 on 5/27/2022.
//

#ifndef OS_DESIGN_PATTERN_OBJECT_ACTIVE_H
#define OS_DESIGN_PATTERN_OBJECT_ACTIVE_H


#include "queue.h"

enum active_status{Running, Stopped};
typedef struct  active_object{

    void* (*f1)(void *);
    void (*f2)(void *);
    Queue *queue;
    pthread_t* thread;
    int status;
}active_object;


active_object * newAO(Queue* , void * , void *);
void* destroyAO(active_object* );










#endif //OS_DESIGN_PATTERN_OBJECT_ACTIVE_H

//
// Created by 97252 on 4/22/2022.
//

#ifndef THREADS_QUEUE_HPP
#define THREADS_QUEUE_HPP






//#include <bits/pthreadtypes.h>
//#include <pthread.h>


/* Queue Thread safety handlers */
//pthread_mutex_t q_mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t con_peek = PTHREAD_COND_INITIALIZER;
//pthread_cond_t con_dequeue = PTHREAD_COND_INITIALIZER;
//pthread_cond_t con_enqueue = PTHREAD_COND_INITIALIZER;


typedef struct node {
    void* data;
    struct node *next;
} node;


typedef struct Queue {

    node *head;
    int size;

} Queue;

Queue* createQ();

void destoryQ(Queue** queue);

void enQ(Queue** queue,void* n);

void deQ(Queue**  queue);

void* peek(Queue**  queue);

void print_queue(Queue** queue);



#endif //THREADS_QUEUE_HPP

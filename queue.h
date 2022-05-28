//
// Created by 97252 on 4/22/2022.
//

#ifndef THREADS_QUEUE_HPP
#define THREADS_QUEUE_HPP







#include <pthread.h>


/* Queue Thread safety handlers */
enum {Free, Busy};
int queue_resource_counter = 0;

typedef struct node {
    void* data;
    struct node *next;
} node;


typedef struct Queue {

    node *head;
    int size;
    pthread_mutex_t q_mutex;
    pthread_cond_t con_q;


} Queue;

Queue* createQ();

void destoryQ(Queue** queue);

void enQ(Queue** queue,void* n);

void * deQ(Queue**  queue);

void* peek(Queue**  queue);

void print_queue(Queue** queue);



#endif //THREADS_QUEUE_HPP

//
// Created by 97252 on 4/22/2022.
//

#include "queue.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"


Queue *createQ() {


    Queue *shared_qu;
    shared_qu = (Queue *) malloc(sizeof(Queue));
    shared_qu->head = NULL;

    pthread_mutex_init(&shared_qu->q_mutex, NULL);
    pthread_cond_init(&shared_qu->con_q, NULL);

    return shared_qu;
}

void destoryQ(Queue **queue) {

    while ((*queue)->size != 0) {
        deQ(queue);
    }

    pthread_mutex_destroy(&((*queue)->q_mutex));
    pthread_cond_destroy(&((*queue)->con_q));

    free((*queue));
}

void enQ(Queue **queue, void *n) {

    pthread_mutex_lock(&((*queue)->q_mutex)); // lock the Queue


    while (queue_resource_counter == Busy || (*queue)->size == 0) {
        printf("waiting on enqueue data\n");
        pthread_cond_wait(&((*queue)->con_q), &((*queue)->q_mutex));
    }

    queue_resource_counter = Busy; //write

    /** ~START~ Write DATA CRITICAL SECTION */
    printf("Starting Writing DATA\n");
    sleep(5);
    printf("Finish Writing DATA\n");
    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = n;

    if ((*queue)->head == NULL) {
        (*queue)->head = new_node;

    } else {
        node *last = (*queue)->head;
        while (last->next != NULL) {
            last = last->next;
        }

        last->next = new_node;
    }
    new_node->next = NULL;
    (*queue)->size++;

    /** ~END~ Write DATA CRITICAL SECTION */

    queue_resource_counter = Free; //free to use


    //notify only the first that waiting to write or delete

    pthread_cond_signal(&((*queue)->con_q));

    pthread_mutex_unlock(&((*queue)->q_mutex)); //unlock the Queue




}

void * deQ(Queue **queue) {

    pthread_mutex_lock(&((*queue)->q_mutex)); // lock the Queue


    while (queue_resource_counter == Busy) {
        printf("Waiting on DEQUEUE DATA\n");
        pthread_cond_wait(&((*queue)->con_q), &((*queue)->q_mutex));
    }

    queue_resource_counter = Busy; //delete

    printf("Delete DATA\n");
//    pthread_mutex_unlock(&q_mutex);


    /** ~START~ Delete DATA CRITICAL SECTION */

    if ((*queue)->size == 0) {
        perror("ERROR: Stack is empty");
        return NULL;
    }

    /* store pointer of the first element in the queue,
     * passing to next section with packet */
    node *top = (*queue)->head;
    void * packet = (*top).data;

    (*queue)->head = (*queue)->head->next;
    free(top);
    (*queue)->size--;



    /** ~END~ Delete DATA CRITICAL SECTION */

    queue_resource_counter = Free;

    //notify only the first that waiting to write or delete
    pthread_cond_signal(&((*queue)->con_q));
    pthread_mutex_unlock(&((*queue)->q_mutex));; //unlock the Queue

    return packet;

}

void print_queue(Queue **queue) {

    for (node *i = (*queue)->head; i != NULL; i = i->next) {
        printf("%p --> ", (i->data));
    }
    printf("\n");

}





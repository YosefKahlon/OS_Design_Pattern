//
// Created by 97252 on 4/22/2022.
//

#include "queue.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


Queue *createQ() {


    Queue *shared_qu;
    shared_qu = (Queue *) malloc(sizeof(Queue));
    shared_qu->head = NULL;

    pthread_mutex_init(&q_mutex, NULL);
    pthread_cond_init(&con_peek, NULL);
    pthread_cond_init(&con_dequeue, NULL);
    pthread_cond_init(&con_enqueue, NULL);

    return shared_qu;
}

void destoryQ(Queue **queue) {

    while ((*queue)->size != 0) {
        deQ(queue);
    }

    pthread_mutex_destroy(&q_mutex);
    pthread_cond_destroy(&con_dequeue);
    pthread_cond_destroy(&con_enqueue);
    pthread_cond_destroy(&con_peek);
    free((*queue));
}

void enQ(Queue **queue, void *n) {

    pthread_mutex_lock(&q_mutex); // lock the Queue


    while (queue_resource_counter != 0) {
        printf("waiting on enqueue data\n");
        pthread_cond_wait(&con_enqueue, &q_mutex);
    }

    queue_resource_counter = -2; //write


    pthread_mutex_unlock(&q_mutex);
    /** ~START~ Write DATA CRITICAL SECTION */

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


    pthread_mutex_lock(&q_mutex);
    queue_resource_counter = 0; //free to use

    //notify all other waiting threads for read
    pthread_cond_broadcast(&con_peek);

    //notify only the first that waiting to write or delete
    pthread_cond_signal(&con_dequeue);
    pthread_cond_signal(&con_enqueue);

    pthread_mutex_unlock(&q_mutex); //unlock the Queue




}

void deQ(Queue **queue) {

    pthread_mutex_lock(&q_mutex); // lock the Queue


    while (queue_resource_counter != 0) {
        printf("Waiting on DEQUEUE DATA\n");
        pthread_cond_wait(&con_dequeue, &q_mutex);
    }

    queue_resource_counter = -1; //delete
    pthread_mutex_unlock(&q_mutex);


    /** ~START~ Delete DATA CRITICAL SECTION */

    if ((*queue)->size == 0) {
        perror("ERROR: Stack is empty");
        return;
    }

    node *top = (*queue)->head;
    (*queue)->head = (*queue)->head->next;
    free(top);
    (*queue)->size--;


    /** ~END~ Delete DATA CRITICAL SECTION */

    pthread_mutex_lock(&q_mutex); // lock the mutex

    queue_resource_counter = 0;

    //notify all other waiting threads for read
    pthread_cond_broadcast(&con_peek);

    //notify only the first that waiting to write or delete
    pthread_cond_signal(&con_dequeue);
    pthread_cond_signal(&con_enqueue);

    pthread_mutex_unlock(&q_mutex); //unlock the Queue


}


void *peek(Queue **queue) {


    pthread_mutex_lock(&q_mutex); // lock the Queue
    void *temp;

    // someone is writing
    // 0 free to use
    while (queue_resource_counter < 0) {
        printf("Waiting On READ DATA\n");
        pthread_cond_wait(&con_peek, &q_mutex); //wait until wake up
    }


    queue_resource_counter++;
    pthread_mutex_unlock(&q_mutex);

///** ~START~ READ DATA CRITICAL SECTION */
    if ((*queue)->size == 0) {
        perror("ERROR: Stack is empty");
        //return "ERROR: Stack is empty";
    }
    temp = (*queue)->head->data;

    pthread_mutex_lock(&q_mutex);

    printf("finish READER NUM: %d\n", queue_resource_counter);
    queue_resource_counter--;


    //signal to the first of waiting
    if (queue_resource_counter == 0) {
        pthread_cond_signal(&con_enqueue);
        pthread_cond_signal(&con_dequeue);
    }

    pthread_mutex_unlock(&q_mutex); //unlock the Queue

    return temp;

}

void print_queue(Queue **queue) {

    for (node *i = (*queue)->head; i != NULL; i = i->next) {
        printf("%p --> ", (i->data));
    }
    printf("\n");

}





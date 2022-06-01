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
    (*shared_qu).queue_resource_counter = 0;
    pthread_mutex_init(&shared_qu->q_mutex, NULL);
    pthread_cond_init(&shared_qu->con_q, NULL);

    return shared_qu;
}

void destoryQ(Queue **queue) {

    (*queue)->queue_resource_counter = Free;
    pthread_cond_signal(&(*queue)->con_q);
    while ((*queue)->size != 0) {
        deQ(queue);
        printf("%d size = \n ", (*queue)->size);
    }

    pthread_mutex_destroy(&((*queue)->q_mutex));
    pthread_cond_destroy(&((*queue)->con_q));

    free((*queue));
}

void enQ(Queue **queue, void *n, int fd) {

    pthread_mutex_lock(&((*queue)->q_mutex)); // lock the Queue

    while ((*queue)->queue_resource_counter == Busy) {
        printf("waiting on enqueue data\n");
        pthread_cond_wait(&((*queue)->con_q), &((*queue)->q_mutex));
    }

    (*queue)->queue_resource_counter = Busy; //write


    //   printf("\n PUSH %p  ,data \n", n);

    char *c = (char *) n;
//    printf("\n PUSH %s  ,data \n", c);



    /** ~START~ Write DATA CRITICAL SECTION */
    printf("Starting Writing DATA -> %s\n", (char *) n);
    sleep(5);
    node *new_node = (node *) malloc(sizeof(node) + 1);
//    new_node->data = (char*)n;
//    printf("str length -> %lu\n", );
//    printf("size of -> %lu\n",sizeof *n);
    strcpy(new_node->data, n);
//    printf("Received data: %s\n", new_node->data);


    new_node->fd = fd;

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
    printf("Finish Writing DATA  -> %s\n\n", (char *) n);

    /** ~END~ Write DATA CRITICAL SECTION */

    (*queue)->queue_resource_counter = Free; //free to use


    //notify only the first that waiting to write or delete

    pthread_mutex_unlock(&((*queue)->q_mutex)); //unlock the Queue
    if ((*queue)->size == 1) {
        // TODO
        pthread_cond_signal(&((*queue)->con_q));
    }

}

void *deQ(Queue **queue) {

    pthread_mutex_lock(&((*queue)->q_mutex)); // lock the Queue


    while ((*queue)->queue_resource_counter == Busy || (*queue)->size == 0) {
        printf("Waiting on DEQUEUE DATA\n");
        pthread_cond_wait(&((*queue)->con_q), &((*queue)->q_mutex));
        if ((*queue)->size == 0) {
            return NULL;
        }
    }


    (*queue)->queue_resource_counter = Busy; //delete

    printf("Start DELETE Data --> %s\n", (char *) (*queue)->head);
//    pthread_mutex_unlock(&q_mutex);


    /** ~START~ Delete DATA CRITICAL SECTION */



    /* store pointer of the first element in the queue,
     * passing to next section with packet */
    node *top = (*queue)->head;
    node *packet = (node *) malloc(sizeof(node));
//    packet->data = (char *)(*top).data;
    strcpy(packet->data, (char *) (*top).data);
    packet->fd = (*top).fd;

    (*queue)->head = (*queue)->head->next;
    free(top);
    (*queue)->size--;

    printf("END DELETE DATA --> %s\n", packet->data);


    /** ~END~ Delete DATA CRITICAL SECTION */

    (*queue)->queue_resource_counter = Free;

    //notify only the first that waiting to write or delete
    pthread_mutex_unlock(&((*queue)->q_mutex));; //unlock the Queue
    // ???
    pthread_cond_broadcast(&((*queue)->con_q));

    return packet;

}

void print_queue(Queue **queue) {

    for (node *i = (*queue)->head; i != NULL; i = i->next) {
        printf("%p --> ", (i->data));
    }
    printf("\n");

}





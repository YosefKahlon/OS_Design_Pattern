//
// Created by 97252 on 4/22/2022.
//

#include "queue.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"



Queue* createQ(){
    Queue *shared_qu;
    shared_qu = (Queue *) malloc(sizeof(Queue));
    shared_qu->head = NULL;
    return  shared_qu;
}

void destoryQ(Queue** queue){
    while ((*queue)->size != 0) {
        deQ(queue);
    }

    free((*queue));
}

void enQ(Queue** queue,void* n){
    node *new_node = (node *) malloc(sizeof(node));
//    strcpy(new_node->data, text);
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
}

void deQ(Queue**  queue){
    if((*queue)->size == 0){
        perror("ERROR: Stack is empty");
        return;
    }

    node* top = (*queue)->head;
    (*queue)->head = (*queue)->head->next;
    free(top);
    (*queue)->size--;
}







void *peek(Queue **queue){
    if((*queue)->size == 0){
        perror("ERROR: Stack is empty");
        //return "ERROR: Stack is empty";
    }
    return (*queue)->head->data;
}

void print_queue(Queue **queue) {

    for (node *i = (*queue)->head; i != NULL; i = i->next) {
        printf("%p --> ", (i->data));
    }
    printf("\n");
}


//
//int main() {
//
//    Queue *queue = createQ();
//    enQ(&queue,(void*)5);
//
//
//
//
//    print_queue(&queue);
//
//}

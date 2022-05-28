


#include <stdio.h>
//#include "queue.h"
#include "queue.c"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

Queue *q;


void* add(void *arg) {

    for (int i = 0; i < 1000; ++i) {
        enQ(&q,  i);
        printf("adding to queue \n\n");
    }
//    sleep(1);


}

void* del(void *arg) {
    for (int i = 0; i < 500; ++i) {
        deQ(&q);
        printf(" deleting to queue \n\n");

    }
    sleep(1);

}

int main() {


    q = createQ();
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &add, NULL);
    pthread_create(&thread2, NULL, &del,NULL);

    pthread_join(thread1,NULL);

    pthread_join(thread2,NULL);

    print_queue(&q);
    exit(0);
}

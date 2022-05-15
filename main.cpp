#include <iostream>
<<<<<<< HEAD
#include "queue.h"
#include "queue.c"
//#include "pthread.h"

Queue *shared_qu;
void* qe( void* arg){
    Queue *q = (Queue*)arg;
    //q.print();

    for (int i = 0; i < 10; ++i) {
        enqueue(&shared_qu, "Q_INIT");
    }
    return nullptr;
}

int main() {


    shared_qu = (Queue *) malloc(sizeof(Queue));
    shared_qu->head = NULL;

    pthread_t a;
  //  pthread_t b;

    pthread_create(&a, nullptr, &qe, nullptr);
//
//
//    pthread_create(&b, nullptr, &qe, nullptr);
////    q.createQ();
////
////    q.enQ(5);
////    q.enQ('a');
//
    pthread_join(a, nullptr);

    print_queue(&shared_qu);
//    pthread_join(b, nullptr);
//    q.print();

=======

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
>>>>>>> parent of 89a39e1 (coomit)
}

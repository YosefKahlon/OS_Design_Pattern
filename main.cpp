#include <iostream>
#include "Queue.hpp"
#include "Queue.cpp"
//#include "pthread.h"


void* qe( void* arg){
    Queue *q = (Queue*)arg;
    //q.print();

    for (int i = 0; i < 10; ++i) {
        q->enQ(i);

    }
    return nullptr;
}

int main() {

    Queue q;
    pthread_t a;
    pthread_t b;

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
//    pthread_join(b, nullptr);
//    q.print();

}

//
// Created by 97252 on 5/14/2022.
//

#ifndef OS_DESIGN_PATTERN_QUEUE_HPP
#define OS_DESIGN_PATTERN_QUEUE_HPP

#include "vector"
#include "iostream"
#include "pthread.h"



class Queue {

private:
    /* Queue Thread safety handlers */
    pthread_mutex_t q_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t con_peek = PTHREAD_COND_INITIALIZER;
    pthread_cond_t con_dequeue = PTHREAD_COND_INITIALIZER;
    pthread_cond_t con_enqueue = PTHREAD_COND_INITIALIZER;
    int queue_resource_counter = 0;


    std::vector<double> *queue{};
    bool exist = false;


public:


    void createQ();

    ~Queue();

    void destoryQ();

    void enQ(double n);

    void deQ();

    void print();


};


#endif //OS_DESIGN_PATTERN_QUEUE_HPP

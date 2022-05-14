//
// Created by 97252 on 5/14/2022.
//

#include "Queue.hpp"


void Queue::createQ() {
    if (!exist) {
        queue = new std::vector<double>;
        exist = true;
    }
}

void Queue::enQ(double n) {
    printf("HERE\n");
    pthread_mutex_lock(&(this->q_mutex)); // lock the Queue
    while (queue_resource_counter != 0) {
        printf("waiting on enqueue data\n");
        pthread_cond_wait(&con_enqueue, &q_mutex);
    }
    queue_resource_counter = -2;
    printf("HERE2\n");

    pthread_mutex_unlock(&q_mutex);

    /** ~START~ Write DATA CRITICAL SECTION */
    if (exist) {
        this->queue->push_back(n);
    }

    /** ~END~ Write DATA CRITICAL SECTION */
    pthread_mutex_lock(&q_mutex);
    queue_resource_counter = 0;
    // notify all other waiting threads
    pthread_cond_broadcast(&con_peek);
    pthread_cond_signal(&con_dequeue);
    pthread_cond_signal(&con_enqueue);

    pthread_mutex_unlock(&q_mutex); //unlock the Queue


}

void Queue::deQ() {

    pthread_mutex_lock(&q_mutex); // lock the Queue
    while (queue_resource_counter != 0) {
        printf("Waiting on DEQUEUE DATA\n");
        pthread_cond_wait(&con_dequeue, &q_mutex);
    }
    queue_resource_counter = -1;
    pthread_mutex_unlock(&q_mutex);

    /** ~START~ Delete DATA CRITICAL SECTION */

    if (!exist) {
        throw std::invalid_argument("queue is not exist !");
    }

    if (this->queue->empty()) {
        throw std::invalid_argument("queue is empty !");
    }

    this->queue->erase(this->queue->begin());


    /** ~END~ Delete DATA CRITICAL SECTION */

    pthread_mutex_lock(&q_mutex); // lock the mutex

    queue_resource_counter = 0;
    pthread_cond_broadcast(&con_peek);
    pthread_cond_signal(&con_dequeue);
    pthread_cond_signal(&con_enqueue);

    pthread_mutex_unlock(&q_mutex); //unlock the Queue

}

void Queue::print() {
    pthread_mutex_lock(&q_mutex); // lock the Queue
    while (queue_resource_counter < 0) {
        printf("Waiting On READ DATA\n");
        pthread_cond_wait(&con_peek, &q_mutex);
    }
    queue_resource_counter++;
    pthread_mutex_unlock(&q_mutex);

/** ~START~ READ DATA CRITICAL SECTION */
    for (double s: *this->queue) {
        std::cout << s << ", ";
    }
    std::cout << "\n";

/** ~END~ READ DATA CRITICAL SECTION */

    pthread_mutex_lock(&q_mutex);
    printf("finish READER NUM: %d\n", queue_resource_counter);
    queue_resource_counter--;
    if (queue_resource_counter == 0) {
        pthread_cond_signal(&con_enqueue);
        pthread_cond_signal(&con_dequeue);
    }
    pthread_mutex_unlock(&q_mutex); //unlock the Queue

}


void Queue::destoryQ() {
    if (exist) {
        delete queue;
        exist = false;
    }
}


Queue::~Queue() {
    if (exist) {
        destoryQ();
    }
}
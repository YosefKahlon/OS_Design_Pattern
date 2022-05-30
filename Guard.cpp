#include <stdio.h>
#include <stdlib.h>

#include "pthread.h"
// #include <Guard.cpp>

pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;



class Guard {      // The class
private:             // Access specifier
    pthread_mutex_t *lock;
public:
    Guard(pthread_mutex_t* lock) {
        this->lock = lock;
        pthread_mutex_lock(this->lock);
    }
    ~Guard() { pthread_mutex_unlock(this->lock); }
};







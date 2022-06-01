#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"



pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;


class Guard {      // The class
private:             // Access specifier
    pthread_mutex_t *lock;
public:
    explicit Guard(pthread_mutex_t *lock) {
        this->lock = lock;
        pthread_mutex_lock(this->lock);
    }

    ~Guard() { pthread_mutex_unlock(this->lock); }
};


/**
 *  Answer:

 *  We can't use guard to lock strtok() method because strtok save a static pointer for reuse in the next time,
 *  in case when multiple threads calls strtok() they effect the same static pointer and my lead to wrong results.
 *
 *  --> in contrast of strtok_r() which require pointer on each call .
 *
 */



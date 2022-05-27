


#include <stdio.h>
#include "queue.h"
#include "queue.c"


int main() {

    Queue * q= createQ();
    enQ(&q, (void*)5);
    print_queue(&q);
    return 0;
}

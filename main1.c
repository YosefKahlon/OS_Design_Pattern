


#include <stdio.h>
#include "queue.h"
#include "string.h"
//#include "queue.c"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include "object_active.h"


Queue *first_q;
Queue *second_q;
Queue *third_q;


//void* add(void *arg) {
//
//    for (int i = 0; i < 1000; ++i) {
//        enQ(&q,  i);
//        printf("adding to queue \n\n");
//    }
////    sleep(1);
//
//
//}

//void* del(void *arg) {
//    for (int i = 0; i < 500; ++i) {
//        deQ(&q);
//        printf(" deleting to queue \n\n");
//
//    }
//    sleep(1);
//
//}

void *encrypt(void *data) {
    char str = (char *) data;
    char temp[1024];

    strcpy(temp, str);


//    temp[0] = 's';
//    char ch;
//    size_t key = 1;
//    for(int i = 0; str[i] != '\0'; ++i){
//        ch = str[i];
//        if(ch >= 'a' && ch <= 'z'){
//            ch = ch + key;
//            if(ch > 'z'){
//                ch = ch - 'z' + 'a' - 1;
//            }
//            str[i] = ch;
//        }
//        else if(ch >= 'A' && ch <= 'Z'){
//            ch = ch + key;
//            if(ch > 'Z'){
//                ch = ch - 'Z' + 'A' - 1;
//            }
//            str[i] = ch;
//        }
//    }
    return temp;
}

//void * pass_to_second(void * data) {
//    enQ(&second_q, data);
//}
//
//void * upper_lower(void * data) {
//
//}
//
//void * pass_to_third(void * data) {
//
//}
//
//void * send_to_client(void * data) {
//
//}
//
//void * validation(void * data) {
//    printf("Passed the packet %s\n", (char *) data);
//    return NULL;
//}

int main() {
//    first_q = createQ();
//    second_q = createQ();
//    third_q = createQ();
//
//    active_object *activeObject_encrypt = newAO(first_q, encrypt, pass_to_second);
//    active_object *activeObject_UPPER_LOWER = newAO(second_q, upper_lower, pass_to_third);
//    active_object *activeObject_return_to_client = newAO(third_q, send_to_client, validation);

    printf("TEST: %s\n", (char *) encrypt("HI"));


//    pthread_t thread1, thread2;
//
//    pthread_create(&thread1, NULL, &add, NULL);
//    pthread_create(&thread2, NULL, &del,NULL);
//
//    pthread_join(thread1,NULL);
//
//    pthread_join(thread2,NULL);

//    print_queue(&q);
    exit(0);
}

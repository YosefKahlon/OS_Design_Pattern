//
// Created by 97252 on 6/1/2022.
//

#ifndef OS_DESIGN_PATTERN_SINGLETON_CPP
#define OS_DESIGN_PATTERN_SINGLETON_CPP


#include <iostream>
#include <unistd.h>

#include <pthread.h>
#include "Guard.cpp"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

using namespace std;


template<typename T>
class singleton {

private:
    /* Here will be the instance stored. */
    static singleton *onlyInstance;
    T parameter;


    /* Private constructor to prevent instancing. */
    singleton(T para);

    singleton() = default;

    ~singleton() = default;

    singleton(const singleton &) = delete;

    singleton &operator=(const singleton &) = delete;


public:
    /* Static access method. */
    static singleton *Instance(T sing);

    void Destroy();
};

//* Null, because instance will be initialized on demand. */
template<typename T>
singleton<T> *singleton<T>::onlyInstance = nullptr;


template<typename T>
singleton<T>::singleton(T para) {
    parameter = para;
}


template<typename T>
singleton<T> *singleton<T>::Instance(T sing) {
    Guard g{&lock};
    if (onlyInstance == nullptr) {
        onlyInstance = new singleton(sing);
    }
    //sleep(2);
   // printf("this is test\n");
    return onlyInstance;
}

template<typename T>
void singleton<T>::Destroy() {
    Guard g{&lock};
    onlyInstance = nullptr;
    delete onlyInstance;
}

int main() {
    int *instance;



    singleton<int *> *test1;
    singleton<int *> *test2;

     test1 = singleton<int *>::Instance(instance);
     test2 = singleton<int *>::Instance(instance);
    cout << test1 << endl;
    cout << test2 << endl;

    test1 == test2 ?  cout << "works" << endl :  cout << " not work" << endl;


}

#endif //OS_DESIGN_PATTERN_SINGLETON_CPP
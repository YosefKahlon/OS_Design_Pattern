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


    T templatee;


    /* Private constructor to prevent instancing. */
    singleton(T temp);

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
singleton<T>::singleton(T temp) {
    templatee = temp;

}


template<typename T>
singleton<T> *singleton<T>::Instance(T sing) {
    Guard g{&lock};
    if (onlyInstance == nullptr) {
        onlyInstance = new singleton(sing);
    }
    sleep(2);
    printf("this is test\n");
    return onlyInstance;
}

template<typename T>
void singleton<T>::Destroy() {
    Guard g{&lock};
    onlyInstance = nullptr;
    delete onlyInstance;
}

int main() {
    int *a;


    singleton<int *> *b;
    singleton<int *> *c;

     b = singleton<int *>::Instance(a);
     c = singleton<int *>::Instance(a);
    cout << b << endl;
    cout << c << endl;
    if (b == c) {
        cout << "works" << endl;
    } else {
        cout << " not work" << endl;
    }

}

#endif //OS_DESIGN_PATTERN_SINGLETON_CPP
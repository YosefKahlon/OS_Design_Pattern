//
// Created by 97252 on 6/1/2022.
//

#ifndef OS_DESIGN_PATTERN_SINGLETON_HPP
#define OS_DESIGN_PATTERN_SINGLETON_HPP

#include "Guard.cpp"

pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

template<typename T>
class singleton {

private:
    static T *onlyInstance = nullptr;

    ~singleton() {
        delete this->onlyInstance;
    }

public:

    const static T *instance() {
        Guard g{&lock2}
        if (this->onlyInstance == nullptr) {
            this->onlyInstance = new singleton<T>;
        }

        return *(this->onlyInstance);
    }
    
    void Destroy() {
        if (this->onlyInstance != nullptr) {
            ~singleton<>();
        }

    }

};


#endif //OS_DESIGN_PATTERN_SINGLETON_HPP

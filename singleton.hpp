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

    singleton() = default;

    ~singleton() = default;

    singleton(const MySingleton &) = delete;

    singleton &operator=(const MySingleton &) = delete;

    

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
            delete this->onlyInstance;
        }

    }

};


#endif //OS_DESIGN_PATTERN_SINGLETON_HPP

#ifndef _SINGLE_H_
#define _SINGLE_H_

#include <mutex>


template<typename T>
class TypeSingle
{
public:
    inline static T *getInstance()
    {
        if (nullptr == instance)
        {
            sMutex.lock();
            if (nullptr == instance)
            {
                instance = new T();
            }
            sMutex.unlock();
        }

        return instance;
    }

private:
    TypeSingle() = default;

private:
    static std::mutex sMutex;
    static T *instance;
};

template<typename T>
std::mutex TypeSingle<T>::sMutex;

template<typename T>
T *TypeSingle<T>::instance = nullptr;



#endif

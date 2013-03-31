
#ifndef __ALLOC_H
#define __ALLOC_H

#include <stdlib.h>
#include "object.h"

namespace Canvas{
    template <class T = Object>
    class Ref:public Object {
    public:
        typedef T  _orig;
        typedef T* _ref;
        Ref<T>(T&);
        Ref<T>(const T&);
        Ref<T>(T*);
        T& operator *();
        T* operator ->();
        ~Ref();
    private:
        Ref<T>();
        T* inval;   //Interna address.
        int rc; //Reference count.
    };

    template <class T>
    Ref<T>::Ref(T& t){
        inval = &t;
    }

    template <class T>
    Ref<T>::Ref(const T& t){
        inval = (T*)&t;
    }

    template <class T>
    Ref<T>::Ref(T* t){
        inval = t;
    }

    template <class T>
    T& Ref<T>::operator *(){
        return *inval;
    }

    template <class T>
    T* Ref<T>::operator ->(){
        return inval;
    }

    template <class T>
    Ref<T>::~Ref(){
        inval->~T();
    }
}

#endif // __ALLOC_H

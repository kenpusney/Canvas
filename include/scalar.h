
#ifndef __SCALAR_H
#define __SCALAR_H

namespace Canvas{
    namespace Types{
        typedef long I;
        typedef double F;
        typedef char C;
        typedef void* P;
    }
    template <class T>
    class Scalar:public Object{
    public:
        Scalar();
        Scalar(T&);
        Scalar(const T&);
        Scalar(Scalar<T>&);
        Scalar(const Scalar<T>&);
        ~Scalar();
        Scalar<T>& operator++();
        Scalar<T>& operator++(int);
        T operator()() const ;
    private:
        T inval;
    };

    template <class T>
    Scalar<T>::Scalar(T& t){
        inval = t;
    }

    template <class T>
    Scalar<T>::Scalar(const T& t){
        inval = t;
    }

    template <class T>
    Scalar<T>::Scalar(Scalar<T>& t){
        inval = t();
    }

    template <class T>
    Scalar<T>::Scalar(const Scalar<T>& t){
        inval = t();
    }

    template <class T>
    Scalar<T>::~Scalar(){

    }

    template <class T>
    Scalar<T>& Scalar<T>::operator++() {
        Scalar<T> temp(*this);
        inval++;
        return temp;
    }

    template <class T>
    T Scalar<T>::operator()() const{
        return inval;
    }
}

#endif // __SCALAR_H

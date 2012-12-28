
#ifndef __SCALAR_H
#define __SCALAR_H

#include "object.h"

template<class T>
class Scalar:public Object,public Comparable< Scalar<T> >{
public:
    typedef Object base;
    typedef T orig_t;
    static const int is_scalar = 1;
    Scalar<T>(){
        __value = (T)0;
        setBytes(sizeof(__value));
    }
    Scalar<T>(double t){
        __value = (T)t;
        setBytes(sizeof(__value));
    }
    Scalar<T>(const Scalar<T>& i){
        this->__value = i.__value;
    }

    void setBytes(int i){bytes = i;}

    int size(){return bytes;}
    int size() const{return bytes;}
    int to_i(){
        return (int)__value;
    }
    int to_i() const{
        return (int)__value;
    }

    /*
     *  Copy Function
     */
    Scalar<T>& operator=(const T i){
        this->__value = i;
        return (*this);
    }
    template <class T2>
    Scalar<T>& operator=(Scalar<T2> t){
        this->value() = (T)t.value();
        return *this;
    }
    template<class T2>
    Scalar<double> operator+(T2 t){
        if(traits<T2>::is_pod)
            return Scalar<double>(this->value()+t);
        return 0.0;
    }
    template<class T2>
    Scalar<double> operator+(Scalar<T2> t){
        return Scalar<double>(this->value()+t.value());
    }
    template<class T2>
    Scalar<double> operator-(T2 t){
        if(traits<T2>::is_pod)
            return Scalar<double>(this->value()-t);
        return 0.0;
    }
    template<class T2>
    Scalar<double> operator-(Scalar<T2> t){
        return Scalar<double>(this->value()-t.value());
    }
    template<class T2>
    Scalar<double> operator*(T2 t){
        if(traits<T2>::is_pod)
            return Scalar<double>(this->value()*t);
        return 0.0;
    }
    template<class T2>
    Scalar<double> operator*(Scalar<T2> t){
        return Scalar<double>(this->value()*t.value());
    }
    template<class T2>
    Scalar<double> operator/(T2 t){
        if(traits<T2>::is_pod)
            return Scalar<double>(this->value()/t);
        return 0.0;
    }
    template<class T2>
    Scalar<double> operator/(Scalar<T2> t){
        return Scalar<double>(this->value()/t.value());
    }
    Scalar<T>& copy(Scalar<T>& t){
        base::copy(t);
        this->value() = t.value();
    }

    /*Aritmetic Operator*/
    Scalar<T>& operator++(){
        ++__value;
        return *this;
    }
    Scalar<T>& operator--(){
        --__value;
        return *this;
    }
    T operator++(int){
        return __value++;
    }
    T operator--(int){
        return __value--;
    }

    /*Comparion Function*/
    int cmp(Scalar<T>& t2){
        if (this->value() < t2.value())
            return -1;
        else if (this->value() > t2.value())
            return 1;
        else
            return 0;
    }
    int cmp(const Scalar<T>& t2){
        if (this->value() < t2.value())
            return -1;
        else if (this->value() > t2.value())
            return 1;
        else
            return 0;
    }
    int cmp(Scalar<T>& t2) const {
        if (this->value() < t2.value())
            return -1;
        else if (this->value() > t2.value())
            return 1;
        else
            return 0;
    }
    int cmp(const Scalar<T>& t2) const {
        if (this->value() < t2.value())
            return -1;
        else if (this->value() > t2.value())
            return 1;
        else
            return 0;
    }

    T& value(){
        return __value;
    }
    T value() const{
        return __value;
    }
protected:
    T __value;
private:
    int bytes;
};

typedef Scalar<char> Char;
typedef Scalar<unsigned char> Uchar;
typedef Scalar<short> Short;
typedef Scalar<unsigned short> Ushort;
typedef Scalar<int> Integer;
typedef Scalar<unsigned int> Uint;
typedef Scalar<long> Long;
typedef Scalar<unsigned long> Ulong;
typedef Scalar<float> Float;
typedef Scalar<double> Double;

//CHANGE:2012-12-28 00:59:08
//  修改，使得字面值能够出现在二元运算符的左侧。
template<typename T1 = double,class T2>
Scalar<double> operator+(T1 t1,Scalar<T2> t2){
    if(traits<T1>::is_pod)
        return Scalar<double>(t1+t2.value());
    return 0.0;
}
template<typename T1 = double,class T2>
Scalar<double> operator-(T1 t1,Scalar<T2> t2){
    if(traits<T1>::is_pod)
        return Scalar<double>(t1-t2.value());
    return 0.0;
}
template<typename T1 = double,class T2>
Scalar<double> operator*(T1 t1,Scalar<T2> t2){
    if(traits<T1>::is_pod)
        return Scalar<double>(t1*t2.value());
    return 0.0;
}
template<typename T1 = double,class T2>
Scalar<double> operator/(T1 t1,Scalar<T2> t2){
    if(traits<T1>::is_pod)
        return Scalar<double>(t1/t2.value());
    return 0.0;
}

#endif /*__SCALAR_H*/

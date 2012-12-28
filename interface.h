
#ifndef __INTERFACE_H
#define __INTERFACE_H

class Interface{};

template <class Ret>
struct Callable0:public Interface{
    virtual Ret operator()() = 0;
    virtual Ret operator()() const = 0;
};

template <class Ret,class Arg >
struct Callable1:public Interface{
    virtual Ret operator()(Arg) = 0;
    virtual Ret operator()(Arg) const = 0;
};
template <class Ret,class Arg1,class Arg2>
struct Callable2:public Interface{
    virtual Ret operator()(Arg1,Arg2) = 0;
    virtual Ret operator()(Arg1,Arg2) const = 0;
};

struct Runnable:public Interface{
    virtual void run() = 0;
};

template <class T>
struct Enumerable:public Interface{

};

template <class T>
struct Comparable:public Interface{
    virtual int cmp(T&) = 0;
    virtual int cmp(const T&) = 0;
    virtual int cmp(T&) const = 0;
    virtual int cmp(const T&) const = 0;
    bool operator==(const T& t2){
        return cmp(t2) == 0;
    }
    bool operator!=(const T& t2){
        return cmp(t2) != 0;
    }
    bool operator<(const T& t2){
        return cmp(t2) < 0;
    }
    bool operator<=(const T& t2){
        return not (cmp(t2) > 0);
    }
    bool operator>(const T& t2){
        return cmp(t2) > 0;
    }
    bool operator>=(const T& t2){
        return not (cmp(t2) < 0);
    }
    bool operator==(const T& t2) const {
        return cmp(t2) == 0;
    }
    bool operator!=(const T& t2) const {
        return cmp(t2) != 0;
    }
    bool operator<(const T& t2) const {
        return cmp(t2) < 0;
    }
    bool operator<=(const T& t2) const {
        return not (cmp(t2) > 0);
    }
    bool operator>(const T& t2) const {
        return cmp(t2) > 0;
    }
    bool operator>=(const T& t2) const {
        return not (cmp(t2) < 0);
    }
};

template <class T>
struct Iteratable:public Interface{
    typedef T elem;
};

template <class T>
struct Collectable:public Iteratable<T>{

};

template <class T>

#endif


#ifndef __BOOL_H
#define __BOOL_H

#include "object.h"

class Null:public Object{
public:
    typedef Object base;
    Null(){
        setAddr((void*)0);
    }
    Null(Null& n){}
    ~Null(){}

    int to_i(){
        return 0;
    }
    int to_i() const{
        return 0;
    }
};

class Bool:public Object,public Callable0<bool>{
public:
    typedef Object base;
    Bool(){
        i = 0;
    }
    Bool(int i){
        this->i = i;
    }
    Bool(const Bool& b){
        this->i = b.i;
    }
    bool operator()(){
        return (bool)i;
    }
    bool operator()() const {
        return (bool)i;
    }
    int to_i(){
        return i;
    }
    int to_i() const{
        return i;
    }
private:
    int i;
};

#endif /*__BOOL_H*/

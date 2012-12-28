
#ifndef __OBJECT_H
#define __OBJECT_H

#include "traits.h"

class Object{
public:
    typedef Object base;
    static const int is_scalar = 0;
    Object(){
        addr = this;
        object_id++;
    }
    Object(Object & obj){
        this->addr = obj.addr;
        object_id++;
    }
    virtual Object* operator &(){
        return (addr);
    }
    virtual Object& copy(Object& obj){
        this->addr = obj.addr;
        this->object_id = obj.object_id;
        return (*(this->addr));
    }
    virtual int to_i(){
        return 1;
    }
    virtual int to_i() const {
        return 1;
    }
    virtual int getObjectID(){
        return object_id;
    }

    virtual int getObjectID() const {
        return object_id;
    }
    template <class T>
    static bool isPod(T i){
        return traits<T>::is_pod;
    }
    bool isPod(){
        return isPod(*this);
    }
    ~Object(){}
protected:
    void setAddr(Object* a){
        this->addr = a;
    }
    void setAddr(void* a){
        this->addr = (Object*)a;
    }
private:
    Object* addr;
    static int object_id;
};

int Object::object_id = 0;
#endif /*__OBJECT_H*/

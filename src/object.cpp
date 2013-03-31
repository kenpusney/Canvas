
#include "object.h"

namespace Canvas{

    BaseObject::BaseObject(){
        object_count++;
    }

    BaseObject::~BaseObject(){

    }

    int BaseObject::getObjectCount(){
        return object_count;
    }

    Object::Object(){
        addr = this;
        object_id = getObjectCount();
    }

    Object::Object(Object & obj){
        addr = this;
        object_id = getObjectCount();
    }

    Object::Object(const Object & obj){
        addr = this;
        object_id = getObjectCount();
    }

    Object* Object::operator &() const {
        return (addr);
    }

    Object& Object::copy(Object& obj){
        this->addr = obj.addr;
        this->object_id = obj.object_id;
        return (*(this->addr));
    }

    int Object::to_i() const {
        return 1;
    }

    int Object::getObjectID() const {
        return object_id;
    }

    Object::~Object(){}

    void Object::setAddr(Object* a){
        this->addr = a;
    }

    void Object::setAddr(void* a){
        this->addr = (Object*)a;
    }

    int BaseObject::object_count = 0;
}

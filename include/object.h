
#ifndef __OBJECT_H
#define __OBJECT_H

#include "traits.h"

namespace Canvas{
    class BaseObject{
    public:
        typedef BaseObject base;
        BaseObject();
        ~BaseObject();
    protected:
        int getObjectCount();
    private:
        static int object_count;
    };

    class Object: public BaseObject{
    public:
        typedef Object base;
        Object();
        Object(Object&);
        virtual Object* operator &() const ;
        virtual Object& copy(Object &);
        virtual int to_i() const ;
        virtual int getObjectID() const ;
        Object(const Object & obj);
        ~Object();
    protected:
        void setAddr(Object* a);
        void setAddr(void* a);
    private:
        Object* addr;
        int object_id;
    };

}
#endif /*__OBJECT_H*/

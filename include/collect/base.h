
#ifndef __COLLECT_BASE_H
#define __COLLECT_BASE_H

#include "../object.h"

template<class T>
class IEnumerable: public virtual Interface {
    
public:
    ~IEnumerable() = 0;
};

template<class T>
IEnumerable<T>::~IEnumerable() {};
#endif

#ifndef __COLLECT_SEQUENCE_H__
#define __COLLECT_SEQUENCE_H__

#include "common.h"

namespace collect{

    template<class T>
    struct sequence{
        using element_type = T;
        using iter_category = category::iter::bidirectional;
        struct element{
            element* prev;
            element* next;
            T t;
        };

        struct iter{
            element* current;
            using element_type = T;
            element_type& operator*(){
                return current->t;
            };
            element_type* operator->(){
                return &(current->t);
            }
            iter& operator++(){
                current = current->next;
                return *this;
            }
            iter& operator--(){
                current = current->prev;
                return *this;
            }
            bool operator==(const iter& other){
                return current == other.current;
            }
            bool operator!=(const iter& other){
                return current != other.current;
            }
        };

        using iter_type = iter;
        iter_type begin(){
            return head;
        };
        iter_type end(){
            return tail;
        }
    private:
        iter head, tail;
    };
}

#endif // __COLLECT_SEQUENCE_H__

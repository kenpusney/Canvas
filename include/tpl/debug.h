
#ifndef __TPL_DEBUG_H__
#define __TPL_DEBUG_H__

#ifndef UNITTEST_H
#include "../unittest.h"
#endif
#include "boolean.h"
#include <typeinfo>
#include <iostream>

template<class T>
struct AssertTrue{
    AssertTrue() {
        TestPrint("Fail!");
        TestAssert(false);
    }
};

template<>
struct AssertTrue<tpl::boolean::$true>{
    AssertTrue(){
    };
};

template<class cls, class... clses>
struct AssertAll{
    AssertAll(){
        AssertTrue<cls>();
        AssertAll<clses...>();
    };
};
template<class cls>
struct AssertAll<cls>{
    AssertAll(){
        AssertTrue<cls>();
    };
};

#endif
